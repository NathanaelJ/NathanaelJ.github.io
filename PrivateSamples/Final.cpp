
//==========================================================
//  2D Navier Stokes Equation Solver
//  Created      | Sylvain Laizet    | 2014 | Fortran
//  Translated   | Nathanael Jenkins | 2021 | C++
//  Parallelised | Nathanael Jenkins | 2021 | SYCL
//==========================================================
//  Version 4.3
//  C++ solver with SYCL implementation
//  Compile using makefile ONLY
//  Last updated 17.10.2021

//  To-do list:
//    -  Watch for support release for sycl::host_task in hipSYCL and full support in DPC++
//    -  If sycl::host_task support is implemented, use event dependencies for file writing (currently using e15.wait() - note fstream must be copied into host kernel)
//    -  Check for updates on sycl::reduction support and work on optimising average calculations
//    -  Review SYCL and C++ implementation for further efficiency improvements:
//        * Define coef[] outside of RK function (these are constants!)
//        * Define udx and udy outside of derivative functions (these are constants!)
//    -  Consider using more ND_Range kernels?


#include <iostream>     //  Printing (I/O)
#include <fstream>      //  File writing (I/O)
#include <cmath>        //  Math
#if !(SERIAL)
    #include <CL/sycl.hpp>      //  Parallelisation (SYCL)
    #if DPC
        #include "dpc_common.hpp"   //  SYCL DPCPP (Intel) compiler
    #endif
#endif

using namespace std;

//==========================================================
//==========================================================
//  Useful variables

//  'domain', 'timesteps', and 'imod' to be defined by compiler preprocessor (makefile)
const int nx=domain, ny=domain, ns=3, nt=timesteps, imodulo=imod;
const double CFL=0.25;
//  nx x ny => Size of computational domain
//       nt => Number of time steps
//  imodulo => File write frequency

#if !(SERIAL)
    cl::sycl::device d = cl::sycl::device(deviceSelection);
    cl::sycl::queue q(d);  //  Global SYCL queue
    //  device defined by compiler (e.g. cl::sycl::gpu_selector{})
    cl::sycl::event e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, e15, m1, s1, m2, s2, m3, s3, m4, s4, m5, s5, m6, s6, av1, av2, av3, av4, av5, av6;  //  SYCL events for dependencies
#endif





//==========================================================
//==========================================================
//  Functions

//==========================================================
//  Mean value of 2D field
#if AVG
void average(double *uuu,
#if SERIAL
    double &um){
    
    um = 0;
    for(int j=0; j<ny; ++j){
        for(int i=0; i<nx; ++i){
            um += uuu[i+nx*j];
        }
    }
    um /= (nx*ny);
    return;
#else
    double* utm, cl::sycl::event eDep, cl::sycl::event eSend){

    cl::sycl::event avgInit = q.submit([&](cl::sycl::handler &h) {
        h.single_task([=] {
            *utm=0;
        });
    });
    eSend = q.submit([&](cl::sycl::handler &h) {
        h.depends_on({eDep, avgInit});
        h.parallel_for(cl::sycl::nd_range<1>{cl::sycl::range<1>(ny*nx), cl::sycl::range<1>(nx)},
         cl::sycl::reduction(utm, cl::sycl::plus<double>()),
         [=](cl::sycl::nd_item<1> idx, auto& utm)
         {
            int i = idx.get_global_id(0);
            utm += uuu[i];
      });
    });
    q.wait();
    return;
#endif
}
#endif

#if !FOURORDER
//==========================================================
//  First derivative in x-direction
void derix(double *phi, double *dfi, double &xlx
#if !SERIAL
, cl::sycl::event dependent, cl::sycl::event &main, cl::sycl::event &sub
#endif
){
    double udx=nx/(2*xlx);
    
#if SERIAL
    for(int j=0; j<ny; ++j){
        dfi[nx*j]=udx*(phi[nx*j+1]-phi[nx*(j+1)-1]);
        for(int i=1; i<nx-1; ++i){
            dfi[i+nx*j]=udx*(phi[nx*j+i+1]-phi[nx*j+i-1]);
        }
        dfi[nx*(j+1)-1]=udx*(phi[nx*j]-phi[nx*(j+1)-2]);
    }
#else
    main = q.submit([&](auto &h) {
        h.depends_on(dependent);
        h.parallel_for(cl::sycl::range(ny, nx-2), [=](auto idx) {
            int i = idx[1]+1;
            int j = idx[0];
            dfi[i+nx*j]=phi[nx*j+i+1]-phi[nx*j+i-1];
            dfi[i+nx*j]=dfi[i+nx*j] * udx;
        });
    });
    sub = q.submit([&](auto &g) {
        g.depends_on(dependent);
        g.parallel_for(cl::sycl::range(ny), [=](auto idx) {
            int j = idx[0];
            dfi[nx*j]=udx*(phi[nx*j+1]-phi[nx*(j+1)-1]);
            dfi[nx*(j+1)-1]=udx*(phi[nx*j]-phi[nx*(j+1)-2]);
        });
    });
#endif
    return;
}

//==========================================================
//  First derivative in y-direction
void deriy(double *phi, double *dfi, double &yly
#if !SERIAL
           , cl::sycl::event dependent, cl::sycl::event &main, cl::sycl::event &sub
#endif
           ){
    double udy=ny/(2*yly);
#if SERIAL
    for(int j=1; j<ny-1; ++j){
        for(int i=0; i<nx; ++i){
            dfi[i+nx*j]=udy*(phi[nx*(j+1)+i]-phi[nx*(j-1)+i]);
        }
    }
    for(int i=0; i<nx; ++i){
        dfi[i]=udy*(phi[i+nx]-phi[nx*(ny-1)+i]);
        dfi[nx*(ny-1)+i]=udy*(phi[i]-phi[nx*(ny-2)+i]);
    }
#else
    main = q.submit([&](auto &h) {
        h.depends_on(dependent);
        h.parallel_for(cl::sycl::range(ny-2, nx), [=](auto idx) {
            int i = idx[1];
            int j = idx[0]+1;
            dfi[i+nx*j]=phi[nx*(j+1)+i]-phi[nx*(j-1)+i];
            dfi[i+nx*j]=dfi[i+nx*j] * udy;
        });
    });
    sub = q.submit([&](auto &g) {
        g.depends_on(dependent);
        g.parallel_for(cl::sycl::range(nx), [=](auto idx) {
            int i = idx[0];
            dfi[i]=udy*(phi[i+nx]-phi[nx*(ny-1)+i]);
            dfi[nx*(ny-1)+i]=udy*(phi[i]-phi[nx*(ny-2)+i]);
        });
    });
#endif
    return;
}

//==========================================================
//  Second derivative in x-direction
void derxx(double *phi, double *dfi, double &xlx
#if !SERIAL
           , cl::sycl::event dependent, cl::sycl::event &main, cl::sycl::event &sub
#endif
           ){
    double udx=pow(nx,2)/(pow(xlx,2));
#if SERIAL
    for(int j=0; j<ny; ++j){
        dfi[nx*j]=udx*(phi[nx*j+1]-(phi[nx*j]+phi[nx*j])+phi[nx*(j+1)-1]);
        for(int i=1; i<nx-1; ++i){
            dfi[i+nx*j]=udx*(phi[nx*j+i+1]-(phi[i+nx*j]+phi[i+nx*j])+phi[nx*j+i-1]);
        }
        dfi[nx*(j+1)-1]=udx*(phi[nx*j]-(phi[nx*(j+1)-1]+phi[nx*(j+1)-1])+phi[nx*(j+1)-2]);
    }
#else
    main = q.submit([&](auto &h) {
        h.depends_on(dependent);
        h.parallel_for(cl::sycl::range(ny, nx-2), [=](auto idx) {
            int i = idx[1]+1;
            int j = idx[0];
            dfi[i+nx*j]=phi[nx*j+i+1]-(phi[i+nx*j]+phi[i+nx*j])+phi[nx*j+i-1];
            dfi[i+nx*j]=dfi[i+nx*j] * udx;
        });
    });
    sub = q.submit([&](auto &g) {
        g.depends_on(dependent);
        g.parallel_for(cl::sycl::range(ny), [=](auto idx) {
            int j = idx[0];
            dfi[nx*j]=udx*(phi[nx*j+1]-(phi[nx*j]+phi[nx*j])+phi[nx*(j+1)-1]);
            dfi[nx*(j+1)-1]=udx*(phi[nx*j]-(phi[nx*(j+1)-1]+phi[nx*(j+1)-1])+phi[nx*(j+1)-2]);
        });
    });
#endif
    return;
}

//==========================================================
//  Second derivative in y-direction
void deryy(double *phi, double *dfi, double &yly
#if !SERIAL
           , cl::sycl::event dependent, cl::sycl::event &main, cl::sycl::event &sub
#endif
           ){
    double udy=pow(ny,2)/(pow(yly,2));
#if SERIAL
    for(int j=1; j<ny-1; ++j){
        for(int i=0; i<nx; ++i){
            dfi[i+nx*j]=udy*(phi[nx*(j+1)+i]-(phi[i+nx*j]+phi[i+nx*j])+phi[nx*(j-1)+i]);
        }
    }
    for(int i=0; i<nx; ++i){
        dfi[i]=udy*(phi[i+nx]-(phi[i]+phi[i])+phi[nx*(ny-1)+i]);
        dfi[nx*(ny-1)+i]=udy*(phi[i]-(phi[nx*(ny-1)+i]+phi[nx*(ny-1)+i])+phi[nx*(ny-2)+i]);
    }
#else
    main = q.submit([&](auto &h) {
        h.depends_on(dependent);
        h.parallel_for(cl::sycl::range(ny-2, nx), [=](auto idx) {
            int i = idx[1];
            int j = idx[0]+1;
            dfi[i+nx*j]=phi[nx*(j+1)+i]-(phi[i+nx*j]+phi[i+nx*j])+phi[nx*(j-1)+i];
            dfi[i+nx*j]=dfi[i+nx*j] * udy;
        });
    });
    sub = q.submit([&](auto &g) {
        g.depends_on(dependent);
        g.parallel_for(cl::sycl::range(nx), [=](auto idx) {
            int i = idx[0];
            dfi[i]=udy*(phi[i+nx]-(phi[i]+phi[i])+phi[nx*(ny-1)+i]);
            dfi[nx*(ny-1)+i]=udy*(phi[i]-(phi[nx*(ny-1)+i]+phi[nx*(ny-1)+i])+phi[nx*(ny-2)+i]);
        });
    });
#endif
    return;
}
                     
//  Second deriy subroutine with additional dependencies
#if !SERIAL
 void deriy2(double *phi, double *dfi, double &yly, cl::sycl::event dependent1, cl::sycl::event dependent2, cl::sycl::event &main, cl::sycl::event &sub){
     double udy=ny/(2*yly);

     main = q.submit([&](auto &h) {
         h.depends_on(dependent1);
         h.parallel_for(cl::sycl::range(ny-2, nx), [=](auto idx) {
             int i = idx[1];
             int j = idx[0]+1;
             dfi[i+nx*j]=phi[nx*(j+1)+i]-phi[nx*(j-1)+i];
             dfi[i+nx*j]=dfi[i+nx*j] * udy;
         });
     });
     sub = q.submit([&](auto &g) {
         g.depends_on(dependent2);
         g.parallel_for(cl::sycl::range(nx), [=](auto idx) {
             int i = idx[0];
             dfi[i]=udy*(phi[i+nx]-phi[nx*(ny-1)+i]);
             dfi[nx*(ny-1)+i]=udy*(phi[i]-phi[nx*(ny-2)+i]);
         });
     });
     return;
  }
#endif

#else // Fourth order derivatives (start)

//==========================================================
//  4th order first derivative in x-direction
void derix(double *phi, double *dfi, double &xlx
#if !SERIAL
, cl::sycl::event dependent, cl::sycl::event &main, cl::sycl::event &sub
#endif
){
    double udx=nx/(12*xlx);
 
#if SERIAL
    for(int j=0; j<ny; ++j){
        dfi[nx*j]=udx*(phi[nx*(j+1)-2]-8*phi[nx*(j+1)-1]+8*phi[nx*j+1]-phi[nx*j+2]);
        dfi[nx*j+1]=udx*(phi[nx*(j+1)-1]-8*phi[nx*j]+8*phi[nx*j+2]-phi[nx*j+3]);
        for(int i=2; i<nx-2; ++i){
            dfi[i+nx*j]=udx*(phi[nx*j+i-2]-8*phi[nx*j+i-1]+8*phi[nx*j+i+1]-phi[nx*j+i+2]);
        }
        dfi[nx*(j+1)-2]=udx*(phi[nx*(j+1)-4]-8*phi[nx*(j+1)-3]+8*phi[nx*(j+1)-1]-phi[nx*j]);
        dfi[nx*(j+1)-1]=udx*(phi[nx*(j+1)-3]-8*phi[nx*(j+1)-2]+8*phi[nx*j]-phi[nx*j+1]);
    }
#else
    main = q.submit([&](auto &h) {
        h.depends_on(dependent);
        h.parallel_for(cl::sycl::range(ny, nx-4), [=](auto idx) {
            int i = idx[1]+2;
            int j = idx[0];
            dfi[i+nx*j]=phi[nx*j+i-2]-8*phi[nx*j+i-1]+8*phi[nx*j+i+1]-phi[nx*j+i+2];
            dfi[i+nx*j] = udx*dfi[i+nx*j];
        });
    });
    sub = q.submit([&](auto &g) {
        g.depends_on(dependent);
        g.parallel_for(cl::sycl::range(ny), [=](auto idx) {
            int j = idx[0];
            dfi[nx*j]=udx*(phi[nx*(j+1)-2]-8*phi[nx*(j+1)-1]+8*phi[nx*j+1]-phi[nx*j+2]);
            dfi[nx*j+1]=udx*(phi[nx*(j+1)-1]-8*phi[nx*j]+8*phi[nx*j+2]-phi[nx*j+3]);
            dfi[nx*(j+1)-2]=udx*(phi[nx*(j+1)-4]-8*phi[nx*(j+1)-3]+8*phi[nx*(j+1)-1]-phi[nx*j]);
            dfi[nx*(j+1)-1]=udx*(phi[nx*(j+1)-3]-8*phi[nx*(j+1)-2]+8*phi[nx*j]-phi[nx*j+1]);
        });
    });
#endif
    return;
}

//==========================================================
//  4th order first derivative in y-direction
void deriy(double *phi, double *dfi, double &yly
#if !SERIAL
        , cl::sycl::event dependent, cl::sycl::event &main, cl::sycl::event &sub
#endif
        ){
    double udy=ny/(12*yly);
#if SERIAL
    for(int j=2; j<ny-2; ++j){
        for(int i=0; i<nx; ++i){
            dfi[i+nx*j]=udy*(phi[nx*(j-2)+i]-8*phi[nx*(j-1)+i]+8*phi[nx*(j+1)+i]-phi[nx*(j+2)+i]);
        }
    }
    for(int i=0; i<nx; ++i){
        dfi[i]=udy*(phi[nx*(ny-2)+i]-8*phi[nx*(ny-1)+i]+8*phi[i+nx]-phi[i+2*nx]);
        dfi[nx+i]=udy*(phi[nx*(ny-1)+i]-8*phi[i]+8*phi[i+nx*2]-phi[i+nx*3]);
        dfi[nx*(ny-2)+i]=udy*(phi[nx*(ny-4)+i]-8*phi[nx*(ny-3)+i]+8*phi[nx*(ny-1)+i]-phi[i]);
        dfi[nx*(ny-1)+i]=udy*(phi[nx*(ny-3)+i]-8*phi[nx*(ny-2)+i]+8*phi[i]-phi[nx+i]);
    }
#else
    main = q.submit([&](auto &h) {
        h.depends_on(dependent);
        h.parallel_for(cl::sycl::range(ny-4, nx), [=](auto idx) {
            int i = idx[1];
            int j = idx[0]+2;
            dfi[i+nx*j]=phi[nx*(j-2)+i]-8*phi[nx*(j-1)+i]+8*phi[nx*(j+1)+i]-phi[nx*(j+2)+i];
            dfi[i+nx*j]=dfi[i+nx*j] * udy;
        });
    });
    sub = q.submit([&](auto &g) {
        g.depends_on(dependent);
        g.parallel_for(cl::sycl::range(nx), [=](auto idx) {
             int i = idx[0];
             dfi[i]=udy*(phi[nx*(ny-2)+i]-8*phi[nx*(ny-1)+i]+8*phi[i+nx]-phi[i+2*nx]);
             dfi[nx+i]=udy*(phi[nx*(ny-1)+i]-8*phi[i]+8*phi[i+nx*2]-phi[i+nx*3]);
             dfi[nx*(ny-2)+i]=udy*(phi[nx*(ny-4)+i]-8*phi[nx*(ny-3)+i]+8*phi[nx*(ny-1)+i]-phi[i]);
             dfi[nx*(ny-1)+i]=udy*(phi[nx*(ny-3)+i]-8*phi[nx*(ny-2)+i]+8*phi[i]-phi[nx+i]);
        });
    });
#endif
    return;
}

//==========================================================
//  4th order second derivative in x-direction
void derxx(double *phi, double *dfi, double &xlx
#if !SERIAL
        , cl::sycl::event dependent, cl::sycl::event &main, cl::sycl::event &sub
#endif
        ){
    double udx=pow(nx,2)/(12*pow(xlx,2));
#if SERIAL
    for(int j=0; j<ny; ++j){
        dfi[nx*j]=udx*(-phi[nx*(j+1)-2]+16*phi[nx*(j+1)-1]+16*phi[nx*j+1]-phi[nx*j+2]-30*phi[nx*j]);
        dfi[nx*j+1]=udx*(-phi[nx*(j+1)-1]+16*phi[nx*j]+16*phi[nx*j+2]-phi[nx*j+3]-30*phi[nx*j+1]);
        for(int i=2; i<nx-2; ++i){
            dfi[i+nx*j]=udx*(-phi[nx*j+i-2]+16*phi[nx*j+i-1]+16*phi[nx*j+i+1]-phi[nx*j+i+2]-30*phi[i+nx*j]);
        }
        dfi[nx*(j+1)-2]=udx*(-phi[nx*(j+1)-4]+16*phi[nx*(j+1)-3]+16*phi[nx*(j+1)-1]-phi[nx*j]-30*phi[nx*(j+1)-2]);
        dfi[nx*(j+1)-1]=udx*(-phi[nx*(j+1)-3]+16*phi[nx*(j+1)-2]+16*phi[nx*j]-phi[nx*j+1]-30*phi[nx*(j+1)-1]);
    }
#else
    main = q.submit([&](auto &h) {
        h.depends_on(dependent);
        h.parallel_for(cl::sycl::range(ny, nx-4), [=](auto idx) {
            int i = idx[1]+2;
            int j = idx[0];
            dfi[i+nx*j]=-phi[nx*j+i-2]=16*phi[nx*j+i-1]+16*phi[nx*j+i+1]-phi[nx*j+i+2]-30*phi[i+nx*j];
            dfi[i+nx*j]=dfi[i+nx*j] * udx;
        });
    });
    sub = q.submit([&](auto &g) {
        g.depends_on(dependent);
        g.parallel_for(cl::sycl::range(ny), [=](auto idx) {
            int j = idx[0];
            dfi[nx*j]=udx*(-phi[nx*(j+1)-2]+16*phi[nx*(j+1)-1]+16*phi[nx*j+1]-phi[nx*j+2]-30*phi[nx*j]);
            dfi[nx*j+1]=udx*(-phi[nx*(j+1)-1]+16*phi[nx*j]+16*phi[nx*j+2]-phi[nx*j+3]-30*phi[nx*j+1]);
            dfi[nx*(j+1)-2]=udx*(-phi[nx*(j+1)-4]+16*phi[nx*(j+1)-3]+16*phi[nx*(j+1)-1]-phi[nx*j]-30*phi[nx*(j+1)-2]);
            dfi[nx*(j+1)-1]=udx*(-phi[nx*(j+1)-3]+16*phi[nx*(j+1)-2]+16*phi[nx*j]-phi[nx*j+1]-30*phi[nx*(j+1)-1]);
        });
    });
#endif
    return;
}

//==========================================================
//  4th order second derivative in y-direction
void deryy(double *phi, double *dfi, double &yly
#if !SERIAL
        , cl::sycl::event dependent, cl::sycl::event &main, cl::sycl::event &sub
#endif
        ){
    double udy=pow(ny,2)/(12*pow(yly,2));
#if SERIAL
    for(int j=2; j<ny-2; ++j){
        for(int i=0; i<nx; ++i){
            dfi[i+nx*j]=udy*(-phi[nx*(j-2)+i]+16*phi[nx*(j-1)+i]+16*phi[nx*(j+1)+i]-phi[nx*(j+2)+i]-30*phi[i+nx*j]);
        }
    }
    for(int i=0; i<nx; ++i){
        dfi[i]=udy*(-phi[nx*(ny-2)+i]+16*phi[nx*(ny-1)+i]+16*phi[i+nx]-phi[i+2*nx]-30*phi[i]);
        dfi[nx+i]=udy*(-phi[nx*(ny-1)+i]+16*phi[i]+16*phi[i+nx*2]-phi[i+nx*3]-30*phi[nx+i]);
        dfi[nx*(ny-2)+i]=udy*(-phi[nx*(ny-4)+i]+16*phi[nx*(ny-3)+i]+16*phi[nx*(ny-1)+i]-phi[i]-30*phi[nx*(ny-2)+i]);
        dfi[nx*(ny-1)+i]=udy*(-phi[nx*(ny-3)+i]+16*phi[nx*(ny-2)+i]+16*phi[i]-phi[nx+i]-30*phi[nx*(ny-1)+i]);
    }
#else
    main = q.submit([&](auto &h) {
        h.depends_on(dependent);
        h.parallel_for(cl::sycl::range(ny-4, nx), [=](auto idx) {
            int i = idx[1];
            int j = idx[0]+2;
            dfi[i+nx*j]=-phi[nx*(j-2)+i]+16*phi[nx*(j-1)+i]+16*phi[nx*(j+1)+i]-phi[nx*(j+2)+i]-30*phi[i+nx*j];
            dfi[i+nx*j]=dfi[i+nx*j] * udy;
        });
    });
    sub = q.submit([&](auto &g) {
        g.depends_on(dependent);
        g.parallel_for(cl::sycl::range(nx), [=](auto idx) {
            int i = idx[0];
            dfi[i]=udy*(-phi[nx*(ny-2)+i]+16*phi[nx*(ny-1)+i]+16*phi[i+nx]-phi[i+2*nx]-30*phi[i]);
            dfi[nx+i]=udy*(-phi[nx*(ny-1)+i]+16*phi[i]+16*phi[i+nx*2]-phi[i+nx*3]-30*phi[nx+i]);
            dfi[nx*(ny-2)+i]=udy*(-phi[nx*(ny-4)+i]+16*phi[nx*(ny-3)+i]+16*phi[nx*(ny-1)+i]-phi[i]-30*phi[nx*(ny-2)+i]);
            dfi[nx*(ny-1)+i]=udy*(-phi[nx*(ny-3)+i]+16*phi[nx*(ny-2)+i]+16*phi[i]-phi[nx+i]-30*phi[nx*(ny-1)+i]);
        });
    });
#endif
    return;
}
                  
//  Second deriy subroutine with additional dependencies
#if !SERIAL
void deriy2(double *phi, double *dfi, double &yly, cl::sycl::event dependent1, cl::sycl::event dependent2, cl::sycl::event &main, cl::sycl::event &sub){
    double udy=ny/(12*yly);
    
    main = q.submit([&](auto &h) {
        h.depends_on(dependent1);
        h.parallel_for(cl::sycl::range(ny-4, nx), [=](auto idx) {
            int i = idx[1];
            int j = idx[0]+2;
            dfi[i+nx*j]=phi[nx*(j-2)+i]-8*phi[nx*(j-1)+i]+8*phi[nx*(j+1)+i]-phi[nx*(j+2)+i];
            dfi[i+nx*j]=dfi[i+nx*j] * udy;
        });
    });
    sub = q.submit([&](auto &g) {
        g.depends_on(dependent2);
        g.parallel_for(cl::sycl::range(nx), [=](auto idx) {
             int i = idx[0];
             dfi[i]=udy*(phi[nx*(ny-2)+i]-8*phi[nx*(ny-1)+i]+8*phi[i+nx]-phi[i+2*nx]);
             dfi[nx+i]=udy*(phi[nx*(ny-1)+i]-8*phi[i]+8*phi[i+nx*2]-phi[i+nx*3]);
             dfi[nx*(ny-2)+i]=udy*(phi[nx*(ny-4)+i]-8*phi[nx*(ny-3)+i]+8*phi[nx*(ny-1)+i]-phi[i]);
             dfi[nx*(ny-1)+i]=udy*(phi[nx*(ny-3)+i]-8*phi[nx*(ny-2)+i]+8*phi[i]-phi[nx+i]);
        });
    });
    return;
}
#endif
                     
#endif // Fourth order derivatives (end)
                     
//==========================================================
//  Right hand side calculations
void fluxx(double *uuu,double *vvv,double *rho,double *pre,double *tmp,double *rou,double *rov,double *roe,double *tb1,double *tb2,double *tb3,double *tb4,double *tb5,double *tb6,double *tb7,double *tb8,double *tb9,double *tba,double *tbb,double *fro,double *fru,double *frv,double *fre,double &xlx,double &yly,double &xmu,double &xba,double *eps,double &eta,double *ftp,double *scp,double &xkt){
    
#if SERIAL
    derix(rou,tb1,xlx);
    deriy(rov,tb2,yly);
    for(int j=0; j<ny; ++j){
        for(int i=0; i<nx; ++i){
            fro[i+nx*j]=-tb1[i+nx*j]-tb2[i+nx*j];
            tb1[i+nx*j]=rou[i+nx*j]*uuu[i+nx*j];
            tb2[i+nx*j]=rou[i+nx*j]*vvv[i+nx*j];
        }
    }
    derix(pre,tb3,xlx);
    derix(tb1,tb4,xlx);
    deriy(tb2,tb5,yly);
    derxx(uuu,tb6,xlx);
    deryy(uuu,tb7,yly);
    derix(vvv,tb8,xlx);
    deriy(tb8,tb9,yly);
    double utt=1.0/3.0;
    double qtt=4.0/3.0;
    for(int j=0; j<ny; ++j){
        for(int i=0; i<nx; ++i){
            tba[i+nx*j]=xmu*(qtt*tb6[i+nx*j]+tb7[i+nx*j]+utt*tb9[i+nx*j]);
            fru[i+nx*j]=-tb3[i+nx*j]-tb4[i+nx*j]-tb5[i+nx*j]+tba[i+nx*j]-((eps[i+nx*j]/eta)*uuu[i+nx*j]);
            tb1[i+nx*j]=rou[i+nx*j]*vvv[i+nx*j];
            tb2[i+nx*j]=rov[i+nx*j]*vvv[i+nx*j];
        }
    }
    deriy(pre,tb3,yly);
    derix(tb1,tb4,xlx);
    deriy(tb2,tb5,yly);
    derxx(vvv,tb6,xlx);
    deryy(vvv,tb7,yly);
    derix(uuu,tb8,xlx);
    deriy(tb8,tb9,yly);
    for(int j=0; j<ny; ++j){
        for(int i=0; i<nx; ++i){
            tbb[i+nx*j]=xmu*(tb6[i+nx*j]+qtt*tb7[i+nx*j]+utt*tb9[i+nx*j]);
            frv[i+nx*j]=-tb3[i+nx*j]-tb4[i+nx*j]-tb5[i+nx*j]+tbb[i+nx*j]-(eps[i+nx*j]/eta)*vvv[i+nx*j];
       }
    }
    derix(scp,tb1,xlx);
    deriy(scp,tb2,yly);
    derxx(scp,tb3,xlx);
    deryy(scp,tb4,yly);
    for(int j=0; j<ny; ++j){
        for(int i=0; i<nx; ++i){
            ftp[i+nx*j]=-uuu[i+nx*j]*tb1[i+nx*j]-vvv[i+nx*j]*tb2[i+nx*j]+xkt*(tb3[i+nx*j]+tb4[i+nx*j])-(eps[i+nx*j]/eta)*scp[i+nx*j];
        }
    }
    derix(uuu,tb1,xlx);
    deriy(vvv,tb2,yly);
    deriy(uuu,tb3,yly);
    derix(vvv,tb4,xlx);
    double dmu=(2.0/3.0)*xmu;
    for(int j=0; j<ny; ++j){
        for(int i=0; i<nx; ++i){
          fre[i+nx*j]=xmu*(uuu[i+nx*j]*tba[i+nx*j]+vvv[i+nx*j]*tbb[i+nx*j])+(xmu+xmu)*(tb1[i+nx*j]*tb1[i+nx*j]+tb2[i+nx*j]*tb2[i+nx*j])-dmu*(tb1[i+nx*j]+tb2[i+nx*j])*(tb1[i+nx*j]+tb2[i+nx*j])+xmu*(tb3[i+nx*j]+tb4[i+nx*j])*(tb3[i+nx*j]+tb4[i+nx*j]);
            tb1[i+nx*j]=roe[i+nx*j]*uuu[i+nx*j];
            tb2[i+nx*j]=pre[i+nx*j]*uuu[i+nx*j];
            tb3[i+nx*j]=roe[i+nx*j]*vvv[i+nx*j];
            tb4[i+nx*j]=pre[i+nx*j]*vvv[i+nx*j];
        }
    }
    derix(tb1,tb5,xlx);
    derix(tb2,tb6,xlx);
    deriy(tb3,tb7,yly);
    deriy(tb4,tb8,yly);
    derxx(tmp,tb9,xlx);
    deryy(tmp,tba,yly);
    for(int j=0; j<ny; ++j){
        for(int i=0; i<nx; ++i){
            fre[i+nx*j]=fre[i+nx*j]-tb5[i+nx*j]-tb6[i+nx*j]-tb7[i+nx*j]-tb8[i+nx*j]+xba*(tb9[i+nx*j]+tba[i+nx*j]);
        }
    }
#else
    derix(rou,tb1,xlx, e1, m1, s1);
    deriy(rov,tb2,yly, e1, m2, s2);
    e2 = q.submit([=] (auto &h) {
        h.depends_on({m1, s1, m2, s2});
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            fro[i+nx*j]=-tb1[i+nx*j]-tb2[i+nx*j];
            tb1[i+nx*j]=rou[i+nx*j]*uuu[i+nx*j];
            tb2[i+nx*j]=rou[i+nx*j]*vvv[i+nx*j];
        });
    });
    derix(pre,tb3,xlx, e1, m1, s1);
    derix(tb1,tb4,xlx, e2, m2, s2);
    deriy(tb2,tb5,yly, e2, m3, s3);
    derxx(uuu,tb6,xlx, e1, m4, s4);
    deryy(uuu,tb7,yly, e1, m5, s5);
    derix(vvv,tb8,xlx, e1, m6, s6);
    deriy2(tb8,tb9,yly, m6, s6, m6, s6);
    double utt=1.0/3.0;
    double qtt=4.0/3.0;
    e3 = q.submit([=] (auto &h) {
        h.depends_on({m1, s1, m2, s2, m3, s3, m4, s4, m5, s5, m6, s6});
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            tba[i+nx*j]=xmu*(qtt*tb6[i+nx*j]+tb7[i+nx*j]+utt*tb9[i+nx*j]);
            fru[i+nx*j]=-tb3[i+nx*j]-tb4[i+nx*j]-tb5[i+nx*j]+tba[i+nx*j]-((eps[i+nx*j]/eta)*uuu[i+nx*j]);
            tb1[i+nx*j]=rou[i+nx*j]*vvv[i+nx*j];
            tb2[i+nx*j]=rov[i+nx*j]*vvv[i+nx*j];
        });
    });
    deriy(pre,tb3,yly, e3, m1, s1);
    derix(tb1,tb4,xlx, e3, m2, s2);
    deriy(tb2,tb5,yly, e3, m3, s3);
    derxx(vvv,tb6,xlx, e3, m4, s4);
    deryy(vvv,tb7,yly, e3, m5, s5);
    derix(uuu,tb8,xlx, e3, m6, s6);
    deriy2(tb8,tb9,yly, m6, s6, m6, s6);
    e4 = q.submit([=] (auto &h) {
        h.depends_on({m1, s1, m2, s2, m3, s3, m4, s4, m5, s5, m6, s6});
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            tbb[i+nx*j]=xmu*(tb6[i+nx*j]+qtt*tb7[i+nx*j]+utt*tb9[i+nx*j]);
            frv[i+nx*j]=-tb3[i+nx*j]-tb4[i+nx*j]-tb5[i+nx*j]+tbb[i+nx*j]-(eps[i+nx*j]/eta)*vvv[i+nx*j];
        });
    });
    derix(scp,tb1,xlx, e3, m1, s1);
    deriy(scp,tb2,yly, e3, m2, s2);
    derxx(scp,tb3,xlx, e4, m3, s3);
    deryy(scp,tb4,yly, e4, m4, s4);
    e5 = q.submit([=] (auto &h) {
        h.depends_on({m1, s1, m2, s2, m3, s3, m4, s4});
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            ftp[i+nx*j]=-uuu[i+nx*j]*tb1[i+nx*j]-vvv[i+nx*j]*tb2[i+nx*j]+xkt*(tb3[i+nx*j]+tb4[i+nx*j])-(eps[i+nx*j]/eta)*scp[i+nx*j];
        });
    });
    derix(uuu,tb1,xlx, e5, m1, s1);
    deriy(vvv,tb2,yly, e5, m2, s2);
    deriy(uuu,tb3,yly, e5, m3, s3);
    derix(vvv,tb4,xlx, e5, m4, s4);
    double dmu=(2.0/3.0)*xmu;
    e6 = q.submit([=] (auto &h) {
        h.depends_on({m1, s1, m2, s2, m3, s3, m4, s4});
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            fre[i+nx*j]=xmu*(uuu[i+nx*j]*tba[i+nx*j]+vvv[i+nx*j]*tbb[i+nx*j])+(xmu+xmu)*(tb1[i+nx*j]*tb1[i+nx*j]+tb2[i+nx*j]*tb2[i+nx*j])-dmu*(tb1[i+nx*j]+tb2[i+nx*j])*(tb1[i+nx*j]+tb2[i+nx*j])+xmu*(tb3[i+nx*j]+tb4[i+nx*j])*(tb3[i+nx*j]+tb4[i+nx*j]);
            tb1[i+nx*j]=roe[i+nx*j]*uuu[i+nx*j];
            tb2[i+nx*j]=pre[i+nx*j]*uuu[i+nx*j];
            tb3[i+nx*j]=roe[i+nx*j]*vvv[i+nx*j];
            tb4[i+nx*j]=pre[i+nx*j]*vvv[i+nx*j];
        });
    });
    derix(tb1,tb5,xlx, e6, m1, s1);
    derix(tb2,tb6,xlx, e6, m2, s2);
    deriy(tb3,tb7,yly, e6, m3, s3);
    deriy(tb4,tb8,yly, e6, m4, s4);
    derxx(tmp,tb9,xlx, e5, m5, s5);
    deryy(tmp,tba,yly, e5, m6, s6);
    e7 = q.submit([=] (auto &h) {
        h.depends_on({m1, s1, m2, s2, m3, s3, m4, s4, m5, s5, m6, s6});
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            fre[i+nx*j]=fre[i+nx*j]-tb5[i+nx*j]-tb6[i+nx*j]-tb7[i+nx*j]-tb8[i+nx*j]+xba*(tb9[i+nx*j]+tba[i+nx*j]);
        });
    });
#endif
        
    return;
}

//==========================================================
//  Runge-Kutta time advancement
void rkutta(double *rho,double *rou,double *rov,double *roe,double *fro,double *gro,double *fru,double *gru,double *frv,double *grv,double *fre,double *gre,double *ftp,double *gtp,double *scp,double &dlt,double *coef, int &k){
        
#if SERIAL
    coef[0] = (8.0/15.0)*dlt;
    coef[1] = (5.0/12.0)*dlt;
    coef[2] = 0.75*dlt;
    coef[3] = 0;
    coef[4] = (17.0/60.0)*dlt;
    coef[5] = (5.0/12.0)*dlt;
    for(int j=0; j<ny; ++j){
        for(int i=0; i<nx; ++i){
            rho[i+nx*j]+=(coef[k-1]*fro[i+nx*j])-(coef[k+ns-1]*gro[i+nx*j]);
            gro[i+nx*j]=fro[i+nx*j];
            rou[i+nx*j]+=(coef[k-1]*fru[i+nx*j])-(coef[k+ns-1]*gru[i+nx*j]);
            gru[i+nx*j]=fru[i+nx*j];
            rov[i+nx*j]+=(coef[k-1]*frv[i+nx*j])-(coef[k+ns-1]*grv[i+nx*j]);
            grv[i+nx*j]=frv[i+nx*j];
            roe[i+nx*j]+=(coef[k-1]*fre[i+nx*j])-(coef[k+ns-1]*gre[i+nx*j]);
            gre[i+nx*j]=fre[i+nx*j];
            scp[i+nx*j]+=(coef[k-1]*ftp[i+nx*j])-(coef[k+ns-1]*gtp[i+nx*j]);
            gtp[i+nx*j]=ftp[i+nx*j];
        }
    }
#else
    e1 = q.submit([=] (auto &h){
        h.depends_on(e7);
        h.single_task([=] {
            coef[0] = (8.0/15.0)*dlt;
            coef[1] = (5.0/12.0)*dlt;
            coef[2] = 0.75*dlt;
            coef[3] = 0;
            coef[4] = (17.0/60.0)*dlt;
            coef[5] = (5.0/12.0)*dlt;
        });
    });
    e9 = q.submit([=] (auto &h) {
        h.depends_on({e1, e7});
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            rho[i+nx*j]+=(coef[k-1]*fro[i+nx*j])-(coef[k+ns-1]*gro[i+nx*j]);
            gro[i+nx*j]=fro[i+nx*j];
        });
    });
    e10 = q.submit([=] (auto &g) {
        g.depends_on({e1, e7});
        g.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            rou[i+nx*j]+=(coef[k-1]*fru[i+nx*j])-(coef[k+ns-1]*gru[i+nx*j]);
            gru[i+nx*j]=fru[i+nx*j];
        });
    });
    e11 = q.submit([=] (auto &f) {
        f.depends_on({e1, e7});
        f.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            rov[i+nx*j]+=(coef[k-1]*frv[i+nx*j])-(coef[k+ns-1]*grv[i+nx*j]);
            grv[i+nx*j]=frv[i+nx*j];
        });
    });
    e12 = q.submit([=] (auto &e) {
        e.depends_on({e1, e7});
        e.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            roe[i+nx*j]+=(coef[k-1]*fre[i+nx*j])-(coef[k+ns-1]*gre[i+nx*j]);
            gre[i+nx*j]=fre[i+nx*j];
        });
    });
    e8 = q.submit([=] (auto &d) {
        d.depends_on({e1, e7});
        d.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            scp[i+nx*j]+=(coef[k-1]*ftp[i+nx*j])-(coef[k+ns-1]*gtp[i+nx*j]);
            gtp[i+nx*j]=ftp[i+nx*j];
        });
    });
#endif

    return;
}

//==========================================================
//  Adams-Bashforth time advancement
void adams(double *rho,double *rou,double *rov,double *roe,double *fro,double *gro,double *fru,double *gru,double *frv,double *grv,double *fre,double *gre,double *ftp,double *gtp,double *scp,double &dlt){
    
    double ct1=1.5*dlt;
    double ct2=0.5*dlt;
#if SERIAL
    for(int j=0; j<ny; ++j){
        for(int i=0; i<nx; ++i){
            rho[i+nx*j]+=(ct1*fro[i+nx*j])-(ct2*gro[i+nx*j]);
            gro[i+nx*j]=fro[i+nx*j];
            rou[i+nx*j]+=(ct1*fru[i+nx*j])-(ct2*gru[i+nx*j]);
            gru[i+nx*j]=fru[i+nx*j];
            rov[i+nx*j]+=(ct1*frv[i+nx*j])-(ct2*grv[i+nx*j]);
            grv[i+nx*j]=frv[i+nx*j];
            roe[i+nx*j]+=(ct1*fre[i+nx*j])-(ct2*gre[i+nx*j]);
            gre[i+nx*j]=fre[i+nx*j];
            scp[i+nx*j]+=(ct1*ftp[i+nx*j])-(ct2*gtp[i+nx*j]);
            gtp[i+nx*j]=ftp[i+nx*j];
       }
    }
#else
    e9 = q.submit([=] (auto &h) {
        h.depends_on(e7);
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            rho[i+nx*j]+=(ct1*fro[i+nx*j])-(ct2*gro[i+nx*j]);
            gro[i+nx*j]=fro[i+nx*j];
        });
    });
    e10 = q.submit([=] (auto &g) {
        g.depends_on(e7);
        g.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            rou[i+nx*j]+=(ct1*fru[i+nx*j])-(ct2*gru[i+nx*j]);
            gru[i+nx*j]=fru[i+nx*j];
        });
    });
    e11 = q.submit([=] (auto &f) {
        f.depends_on(e7);
        f.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            rov[i+nx*j]+=(ct1*frv[i+nx*j])-(ct2*grv[i+nx*j]);
            grv[i+nx*j]=frv[i+nx*j];

        });
    });
    e12 = q.submit([=] (auto &e) {
        e.depends_on(e7);
        e.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            roe[i+nx*j]+=(ct1*fre[i+nx*j])-(ct2*gre[i+nx*j]);
            gre[i+nx*j]=fre[i+nx*j];
        });
    });
    e8 = q.submit([=] (auto &d) {
        d.depends_on(e7);
        d.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            scp[i+nx*j]+=(ct1*ftp[i+nx*j])-(ct2*gtp[i+nx*j]);
            gtp[i+nx*j]=ftp[i+nx*j];
        });
    });
#endif

    return;
}

//==========================================================
//  Problem parameters
void param(double &xlx,double &yly,double &xmu,double &xba,double &gma,double &chp,double &roi,double &cci,double &d,double &tpi,double &chv,double &uu0){
    double ren=200.0;
    double mach=0.2;
    double pdl=0.7;
    roi=1.0;
    cci=1.0;
    d=1.0;
    chp=1.0;
    gma=1.4;
      
    chv=chp/gma;
    xlx=4.0*d;
    yly=4.0*d;
    uu0=mach*cci;
    xmu=roi*uu0*d/ren;
    xba=xmu*chp/pdl;
    tpi=pow(cci,2)/(chp*(gma-1));
    
    return;
}

//==========================================================
//  Initialise problem
void initl(double *uuu,double *vvv,double *rho,double *eee,double *pre,double *tmp,double *rou,double *rov,double *roe,double &xlx,double &yly,double &xmu,double &xba,double &gma,double &chp,double &dlx,double &eta,double *eps,double *scp,double &xkt,double &uu0){
    double roi,cci,d,tpi,chv;
    
    param(xlx,yly,xmu,xba,gma,chp,roi,cci,d,tpi,chv,uu0);
    
    dlx=xlx/nx;
    double dly=yly/ny;
    double ct6=(gma-1)/gma;
    eta=0.1;
    eta=eta/2.0;
    double radius=d/2.0;
    xkt=xba/(chp*roi);
    double pi=acos(-1.0);
        
#if SERIAL
    for(int j=0; j<ny; ++j){
        for(int i=0; i<nx; ++i){
            if ((pow((i+1)*dlx-xlx/2.0, 2)+pow((j+1)*dly-yly/2.0,2)) < pow(radius,2)){
                eps[i+nx*j]=1.0;
            }
            else{
                eps[i+nx*j]=0.0;
            }
        }
    }
    for(int j=0; j<ny; ++j){
        for(int i=0; i<nx; ++i){
            uuu[i+nx*j]=uu0;
            vvv[i+nx*j]=0.01*(sin(4*pi*(i+1)*dlx/xlx)+sin(7.0*pi*(i+1)*dlx/xlx))*exp(-pow((j+1)*dly-yly/2.0, 2));
            tmp[i+nx*j]=tpi;
            eee[i+nx*j]=chv*tmp[i+nx*j]+0.5*(uuu[i+nx*j]*uuu[i+nx*j]+vvv[i+nx*j]*vvv[i+nx*j]);
            rho[i+nx*j]=roi;
            pre[i+nx*j]=rho[i+nx*j]*ct6*chp*tmp[i+nx*j];
            rou[i+nx*j]=rho[i+nx*j]*uuu[i+nx*j];
            rov[i+nx*j]=rho[i+nx*j]*vvv[i+nx*j];
            roe[i+nx*j]=rho[i+nx*j]*eee[i+nx*j];
            scp[i+nx*j]=1.0;
        }
    }
#else
    double rSquared = pow(radius, 2);
    e1 = q.submit([=] (auto &h) {
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int j = idx[0];
            int i = idx[1];
            double condition = (pow((i+1)*dlx-xlx/2.0, 2)+pow((j+1)*dly-yly/2.0,2));
            if (condition < rSquared){
                eps[i+nx*j]=1.0;
            }
            else{
                eps[i+nx*j]=0.0;
            }
        });
    });
    e2 = q.submit([=] (auto &h) {
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int j = idx[0];
            int i = idx[1];
            uuu[i+nx*j]=uu0;
            vvv[i+nx*j]=0.01*(sin(4*pi*(i+1)*dlx/xlx)+sin(7.0*pi*(i+1)*dlx/xlx))*exp(-pow((j+1)*dly-yly/2.0, 2));
            tmp[i+nx*j]=tpi;
            eee[i+nx*j]=chv*tmp[i+nx*j]+0.5*(uuu[i+nx*j]*uuu[i+nx*j]+vvv[i+nx*j]*vvv[i+nx*j]);
            rho[i+nx*j]=roi;
            pre[i+nx*j]=rho[i+nx*j]*ct6*chp*tmp[i+nx*j];
            rou[i+nx*j]=rho[i+nx*j]*uuu[i+nx*j];
            rov[i+nx*j]=rho[i+nx*j]*vvv[i+nx*j];
            roe[i+nx*j]=rho[i+nx*j]*eee[i+nx*j];
            scp[i+nx*j]=1.0;
        });
    });
#endif
    
    return;
}

//==========================================================
//  Update u, v, p, and t each time step
void etatt(double *uuu,double *vvv,double *rho,double *pre,double *tmp,double *rou,double *rov,double *roe,double &gma,double &chp){
    double ct7=gma-1.0;
    double ct8=gma/(gma-1.0);
#if SERIAL
    for(int j=0; j<ny; ++j){
        for(int i=0; i<nx; ++i){
            uuu[i+nx*j]=rou[i+nx*j]/rho[i+nx*j];
            vvv[i+nx*j]=rov[i+nx*j]/rho[i+nx*j];
            pre[i+nx*j]=ct7*(roe[i+nx*j]-(0.5*((rou[i+nx*j]*uuu[i+nx*j])+(rov[i+nx*j]*vvv[i+nx*j]))));
            tmp[i+nx*j]=ct8*pre[i+nx*j]/(rho[i+nx*j]*chp);
        }
    }
#else
    e1 = q.submit([=] (auto &h) {
        h.depends_on({e8, e9, e10, e11, e12});
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int j = idx[0];
            int i = idx[1];
            uuu[i+nx*j]=rou[i+nx*j]/rho[i+nx*j];
            vvv[i+nx*j]=rov[i+nx*j]/rho[i+nx*j];
            pre[i+nx*j]=ct7*(roe[i+nx*j]-(0.5*((rou[i+nx*j]*uuu[i+nx*j])+(rov[i+nx*j]*vvv[i+nx*j]))));
            tmp[i+nx*j]=ct8*pre[i+nx*j]/(rho[i+nx*j]*chp);
        });
    });
#endif

    return;
}




//==========================================================
//==========================================================
//  Main Program

int main(){
    //==========================================================
    //  Variable definitions
    const int nf=3, mx=nf*nx, my=nf*ny;
    double xlx,yly,dlx,dx,xmu,xkt,um0,vm0,tm0;
    double xba,gma,chp,eta,uu0,dlt,um=0,vm,tm,x,y,dy;
    //  Arrays allocated to heap memory
#if SERIAL
    //  Note 'malloc' is used rather than 'new' to improve compatibility with SYCL USM 'malloc'
    //  ('new' vectors require different handling and would therefore require essentially totally separate serial code)
    auto uuu = (double*) malloc(sizeof(double)*nx*ny);
    auto vvv = (double*) malloc(sizeof(double)*nx*ny);
    auto rho = (double*) malloc(sizeof(double)*nx*ny);
    auto eee = (double*) malloc(sizeof(double)*nx*ny);
    auto pre = (double*) malloc(sizeof(double)*nx*ny);
    auto tmp = (double*) malloc(sizeof(double)*nx*ny);
    auto rou = (double*) malloc(sizeof(double)*nx*ny);
    auto rov = (double*) malloc(sizeof(double)*nx*ny);
    auto tuu = (double*) malloc(sizeof(double)*nx*ny);
    auto tvv = (double*) malloc(sizeof(double)*nx*ny);
    auto ftp = (double*) malloc(sizeof(double)*nx*ny);
    auto roe = (double*) malloc(sizeof(double)*nx*ny);
    auto tb1 = (double*) malloc(sizeof(double)*nx*ny);
    auto tb2 = (double*) malloc(sizeof(double)*nx*ny);
    auto tb3 = (double*) malloc(sizeof(double)*nx*ny);
    auto tb4 = (double*) malloc(sizeof(double)*nx*ny);
    auto tb5 = (double*) malloc(sizeof(double)*nx*ny);
    auto tb6 = (double*) malloc(sizeof(double)*nx*ny);
    auto tb7 = (double*) malloc(sizeof(double)*nx*ny);
    auto tb8 = (double*) malloc(sizeof(double)*nx*ny);
    auto tb9 = (double*) malloc(sizeof(double)*nx*ny);
    auto gtp = (double*) malloc(sizeof(double)*nx*ny);
    auto scp = (double*) malloc(sizeof(double)*nx*ny);
    auto tba = (double*) malloc(sizeof(double)*nx*ny);
    auto tbb = (double*) malloc(sizeof(double)*nx*ny);
    auto fro = (double*) malloc(sizeof(double)*nx*ny);
    auto fru = (double*) malloc(sizeof(double)*nx*ny);
    auto frv = (double*) malloc(sizeof(double)*nx*ny);
    auto fre = (double*) malloc(sizeof(double)*nx*ny);
    auto gro = (double*) malloc(sizeof(double)*nx*ny);
    auto gru = (double*) malloc(sizeof(double)*nx*ny);
    auto grv = (double*) malloc(sizeof(double)*nx*ny);
    auto gre = (double*) malloc(sizeof(double)*nx*ny);
    auto wz = (double*) malloc(sizeof(double)*nx*ny);
    auto eps = (double*) malloc(sizeof(double)*nx*ny);
    auto coef = (double*) malloc(sizeof(double)*2*ns);
    auto xx = (double*) malloc(sizeof(double)*mx);
    auto yy = (double*) malloc(sizeof(double)*my);
#else
    auto uuu = cl::sycl::malloc_device<double>(nx*ny, q);
    auto vvv = cl::sycl::malloc_device<double>(nx*ny, q);
    auto rho = cl::sycl::malloc_device<double>(nx*ny, q);
    auto eee = cl::sycl::malloc_device<double>(nx*ny, q);
    auto pre = cl::sycl::malloc_device<double>(nx*ny, q);
    auto tmp = cl::sycl::malloc_device<double>(nx*ny, q);
    auto rou = cl::sycl::malloc_device<double>(nx*ny, q);
    auto rov = cl::sycl::malloc_device<double>(nx*ny, q);
    auto tuu = cl::sycl::malloc_device<double>(nx*ny, q);
    auto tvv = cl::sycl::malloc_device<double>(nx*ny, q);
    auto ftp = cl::sycl::malloc_device<double>(nx*ny, q);
    auto roe = cl::sycl::malloc_device<double>(nx*ny, q);
    auto tb1 = cl::sycl::malloc_device<double>(nx*ny, q);
    auto tb2 = cl::sycl::malloc_device<double>(nx*ny, q);
    auto tb3 = cl::sycl::malloc_device<double>(nx*ny, q);
    auto tb4 = cl::sycl::malloc_device<double>(nx*ny, q);
    auto tb5 = cl::sycl::malloc_device<double>(nx*ny, q);
    auto tb6 = cl::sycl::malloc_device<double>(nx*ny, q);
    auto tb7 = cl::sycl::malloc_device<double>(nx*ny, q);
    auto tb8 = cl::sycl::malloc_device<double>(nx*ny, q);
    auto tb9 = cl::sycl::malloc_device<double>(nx*ny, q);
    auto gtp = cl::sycl::malloc_device<double>(nx*ny, q);
    auto scp = cl::sycl::malloc_device<double>(nx*ny, q);
    auto tba = cl::sycl::malloc_device<double>(nx*ny, q);
    auto tbb = cl::sycl::malloc_device<double>(nx*ny, q);
    auto fro = cl::sycl::malloc_device<double>(nx*ny, q);
    auto fru = cl::sycl::malloc_device<double>(nx*ny, q);
    auto frv = cl::sycl::malloc_device<double>(nx*ny, q);
    auto fre = cl::sycl::malloc_device<double>(nx*ny, q);
    auto gro = cl::sycl::malloc_device<double>(nx*ny, q);
    auto gru = cl::sycl::malloc_device<double>(nx*ny, q);
    auto grv = cl::sycl::malloc_device<double>(nx*ny, q);
    auto gre = cl::sycl::malloc_device<double>(nx*ny, q);
    auto wzDevice = cl::sycl::malloc_device<double>(nx*ny, q);
    auto wz = cl::sycl::malloc_host<double>(nx*ny, q);
    auto eps = cl::sycl::malloc_device<double>(nx*ny, q);
    auto coef = cl::sycl::malloc_device<double>(2*ns, q);
    auto xx = cl::sycl::malloc_host<double>(mx, q);
    auto yy = cl::sycl::malloc_host<double>(my, q);
    auto utm = cl::sycl::malloc_device<double>(1, q);
    auto vtm = cl::sycl::malloc_device<double>(1, q);
    auto ttm = cl::sycl::malloc_device<double>(1, q);
    auto utmH = cl::sycl::malloc_host<double>(1, q);
    auto vtmH = cl::sycl::malloc_host<double>(1, q);
    auto ttmH = cl::sycl::malloc_host<double>(1, q);
#endif

    //==========================================================
    // Setup

    // Initial variables
    initl(uuu,vvv,rho,eee,pre,tmp,rou,rov,roe,xlx,yly,xmu,xba,
          gma,chp,dlx,eta,eps,scp,xkt,uu0);
    dx=xlx/nx;
    dy=yly/ny;
    dlt=CFL*dlx;
    
    // Visualisation output setup (host only)
    x=0.0;
    for(int i=0; i<mx; ++i){
        xx[i]=x;
        x+=dx;
    }
    y=0.0;
    for(int j=0; j<my; ++j){
        yy[j]=y;
        y+=dy;
    }

    // Print to screen
    cout << "\n\x1B[32m\e[1m2D Navier-Stokes Solver (Using Explicit USM)\e[0m\033[0m\t\t" << endl;
    cout << "\x1B[32mThe time step of the simulation is " << dlt << "\e[0m\033[0m\t\t" << endl;
#if SERIAL
    cout << "\x1B[31mRunning on host only\e[0m\033[0m\t\t" << endl;
#else
    cout << "\x1B[32mParallelism activated" << endl;
    cout << "Using " << d.get_info<cl::sycl::info::device::name>() << "\e[0m\033[0m\t\t\n";
    #if DPC
        #if AVG
    if (d.is_gpu() || d.is_accelerator()){
        cout << "\x1B\a[31mDPC++ implementation of host_task is incomplete. Program will run very slowly on GPU or accelerator. Consider using a CPU or host device.\e[0m\033[0m\t\t" << endl;;
    }
        #endif
    #else
        #if AVG
    cout << "\x1B\a[31mhipSYCL does not support host_task. Program may run slowly.\e[0m\033[0m\t\t" << endl;
        #endif
    #endif
#endif
    cout << endl << "====================================================================================" << endl;
#if AVG
    printf("  iter |                     uuu |                     vvv |                     scp\n");
    #if SERIAL
    average(uuu,um0);
    average(vvv,vm0);
    average(scp,tm0);
    printf("     0 % 25.12e % 25.12e % 25.12e \n", um0, vm0, tm0);
    #else
    average(uuu, utm, e2, av1);
    average(vvv, vtm, e2, av2);
    average(scp, ttm, e2, av3);
    av4 = q.submit([&](cl::sycl::handler &h) {
        h.depends_on(av1);
        h.memcpy(&utmH[0], utm, 1*sizeof(double));
    });
    av5 = q.submit([&](cl::sycl::handler &h) {
        h.depends_on(av2);
        h.memcpy(&vtmH[0], vtm, 1*sizeof(double));
    });
    av6 = q.submit([&](cl::sycl::handler &h) {
        h.depends_on(av3);
        h.memcpy(&ttmH[0], ttm, 1*sizeof(double));
    });
        #if DPC
    // As of Oct 2021, DPC++ implementation of SYCL only partially supports host_task, so the solver will run much slower on GPU or accelerator devices
    // ^This has also been found to lead to some errors when compiling. To resolve this, the 'if-else' block below should be commented out, along with event e13
    if (d.is_gpu() || d.is_accelerator()){
        av4.wait();
        av5.wait();
        av6.wait();
        printf("     0 % 25.12e % 25.12e % 25.12e \n", *utmH/(nx*ny), *vtmH/(nx*ny), *ttmH/(nx*ny));
    }
    else{
    e13 = q.submit([&](cl::sycl::handler &h) {
        h.depends_on({av4, av5, av6, e13});
        h.host_task([=] {
            printf("     0 % 25.12e % 25.12e % 25.12e \n", *utmH/(nx*ny), *vtmH/(nx*ny), *ttmH/(nx*ny));
        });
    });
    }
        #else
    // As of Oct 2021, hipSYCL does not conform fully to SYCL specifciation, and does not support host_task submissions
    av4.wait();
    av5.wait();
    av6.wait();
    printf("     0 % 25.12e % 25.12e % 25.12e \n", *utmH/(nx*ny), *vtmH/(nx*ny), *ttmH/(nx*ny));
        #endif
    #endif
#else
    cout << "\x1B[31mAverages disabled.\e[0m\033[0m\t\t" << endl;
#endif

    //==========================================================
    // Time loop
    for(int n=1; n<=nt; n++){

#if !ITEMP
        // Adams-Bashforth temporal method
        // Compute RHS
        fluxx(uuu,vvv,rho,pre,tmp,rou,rov,roe,tb1,tb2,
              tb3,tb4,tb5,tb6,tb7,tb8,tb9,tba,tbb,fro,fru,frv,
              fre,xlx,yly,xmu,xba,eps,eta,ftp,scp,xkt);
        // Time advancement
        adams(rho,rou,rov,roe,fro,gro,fru,gru,frv,grv,fre,
              gre,ftp,gtp,scp,dlt);
        // Update fields
        etatt(uuu,vvv,rho,pre,tmp,rou,rov,roe,gma,chp);
#else
        // Runge-Kutta temporal method
        for (int k=1; k<=ns; k++){
            // Compute RHS
            fluxx(uuu,vvv,rho,pre,tmp,rou,rov,roe,tb1,tb2,
                  tb3,tb4,tb5,tb6,tb7,tb8,tb9,tba,tbb,fro,fru,frv,
                  fre,xlx,yly,xmu,xba,eps,eta,ftp,scp,xkt);
            // Time advancement
            rkutta(rho,rou,rov,roe,fro,gro,fru,gru,frv,grv,fre,
                  gre,ftp,gtp,scp,dlt,coef,k);
            // Update fields
            etatt(uuu,vvv,rho,pre,tmp,rou,rov,roe,gma,chp);
        }
#endif

        //==========================================================
        // Save snapshots
        if (n%imodulo==0){
            // Generate results for gnuplot
            cout << "\e[0m\033[0m\x1B[34m\e[1mWriting File...\e[0m\033[0m\t\t\e[F\e[2m" << endl;

            // Vorticity calculation
#if SERIAL
            derix(vvv,tvv,xlx);
            deriy(uuu,tuu,yly);
            for(int j=0; j<=ny; ++j){
                for(int i=0; i<=nx; ++i){
                    wz[i+nx*j]=tvv[i+nx*j]-tuu[i+nx*j];
                }
            }
#else
            derix(vvv,tvv,xlx, e1, m1, s1);
            deriy(uuu,tuu,yly, e1, m2, s2);
            e14 = q.submit([=] (auto &h) {
                h.depends_on({m1, s1, m2, s2});
                h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
                    int j = idx[0];
                    int i = idx[1];
                    wzDevice[i+nx*j]=tvv[i+nx*j]-tuu[i+nx*j];
                });
            });
            e15 = q.submit([&](cl::sycl::handler &h) {
                h.depends_on(e14);
                h.memcpy(&wz[0], wzDevice, nx*ny*sizeof(double));
                  });
#endif
            // Generate file
            int temp = n/imodulo;
            string filename = "vort";
            filename += std::to_string(temp);
            fstream nfichier(filename, ios::out | ios::trunc);
            if (nfichier.is_open()){
#if !SERIAL
            e15.wait();
#endif
            for(int j=0; j<my; ++j){
                for(int i=0; i<mx; ++i){
                    int ii = i%nx;
                    int jj = j%ny;
                    nfichier << xx[i] << " " << yy[j] << " " << wz[ii+nx*jj] << endl;
                }
                nfichier << "\n";
            }
            nfichier.close();
            }
            else {
                cout << "\a" << endl;
                cerr << "\x1B[31m\e[1mUnable to open file\e[0m\033[0m\t\t" << endl;
                exit(-2);
            }
        }
        
        // Compute field averages
#if AVG
    #if SERIAL
        average(uuu,um);
        average(vvv,vm);
        average(scp,tm);
        // Print average values to screen
        printf("%6i % 25.12e % 25.12e % 25.12e \n\e[0m", n, um, vm, tm);
    #else
        average(uuu, utm, e1, av1);
        average(vvv, vtm, e1, av2);
        average(scp, ttm, e1, av3);
        av4 = q.submit([&](cl::sycl::handler &h) {
            h.depends_on(av1);
            h.memcpy(&utmH[0], utm, 1*sizeof(double));
        });
        av5 = q.submit([&](cl::sycl::handler &h) {
            h.depends_on(av2);
            h.memcpy(&vtmH[0], vtm, 1*sizeof(double));
        });
        av6 = q.submit([&](cl::sycl::handler &h) {
            h.depends_on(av3);
            h.memcpy(&ttmH[0], ttm, 1*sizeof(double));
        });
        #if DPC
        // As of Oct 2021, DPC++ implementation of SYCL only partially supports host_task, so the solver will run much slower on GPU or accelerator devices
        // ^This has also been found to lead to some errors when compiling. To resolve this, the 'if-else' block below should be commented out, along with event e13
        if (d.is_gpu() || d.is_accelerator()){
            av4.wait();
            av5.wait();
            av6.wait();
            printf("%6i % 25.12e % 25.12e % 25.12e \n\e[0m", n, *utmH/(nx*ny), *vtmH/(nx*ny), *ttmH/(nx*ny));
        }
        else{
        e13 = q.submit([&](cl::sycl::handler &h) {
            h.depends_on({av4, av5, av6, e13});
            h.host_task([=] {
                printf("%6i % 25.12e % 25.12e % 25.12e \n\e[0m", n, *utmH/(nx*ny), *vtmH/(nx*ny), *ttmH/(nx*ny));
            });
        });
        }
        #else
        // As of Oct 2021, hipSYCL does not conform fully to SYCL specifciation, and does not support host_task submissions
        av4.wait();
        av5.wait();
        av6.wait();
        printf("%6i % 25.12e % 25.12e % 25.12e \n\e[0m", n, *utmH/(nx*ny), *vtmH/(nx*ny), *ttmH/(nx*ny));
        #endif
    #endif
#else
        cout << "\e[0m\033 Iteration " << n << "   \e\n[F";
#endif
    }
    // End of time loop
    
    // Print to screen & error/NaN handling
    cout << "\e[0m\033 ====================================================================================" << endl;
#if SERIAL
    if (isnan(um)) {
#else
    q.wait();
    if (isnan(*utm)) {
#endif
        // Error returned if uuu field contains any NaN values
        cerr << "\a\x1B[31mSimulation complete. NaN in result!\e[0m\033[0m\t\t" << endl;
    }
    else {
        cout << "\x1B[32mDone!\e[0m\033[0m\t\t\a" << endl;
    }
    
    //  Deallocate heap memory to prevent memory leaks
#if SERIAL
    free(uuu);
    free(vvv);
    free(rho);
    free(eee);
    free(pre);
    free(tmp);
    free(rou);
    free(rov);
    free(tuu);
    free(tvv);
    free(ftp);
    free(roe);
    free(tb1);
    free(tb2);
    free(tb3);
    free(tb4);
    free(tb5);
    free(tb6);
    free(tb7);
    free(tb8);
    free(tb9);
    free(gtp);
    free(scp);
    free(tba);
    free(tbb);
    free(fro);
    free(fru);
    free(frv);
    free(fre);
    free(gro);
    free(gru);
    free(grv);
    free(gre);
    free(wz);
    free(eps);
    free(coef);
    free(xx);
    free(yy);
#else
    cl::sycl::free(uuu, q);
    cl::sycl::free(vvv, q);
    cl::sycl::free(rho, q);
    cl::sycl::free(eee, q);
    cl::sycl::free(pre, q);
    cl::sycl::free(tmp, q);
    cl::sycl::free(rou, q);
    cl::sycl::free(rov, q);
    cl::sycl::free(tuu, q);
    cl::sycl::free(tvv, q);
    cl::sycl::free(ftp, q);
    cl::sycl::free(roe, q);
    cl::sycl::free(tb1, q);
    cl::sycl::free(tb2, q);
    cl::sycl::free(tb3, q);
    cl::sycl::free(tb4, q);
    cl::sycl::free(tb5, q);
    cl::sycl::free(tb6, q);
    cl::sycl::free(tb7, q);
    cl::sycl::free(tb8, q);
    cl::sycl::free(tb9, q);
    cl::sycl::free(gtp, q);
    cl::sycl::free(scp, q);
    cl::sycl::free(tba, q);
    cl::sycl::free(tbb, q);
    cl::sycl::free(fro, q);
    cl::sycl::free(fru, q);
    cl::sycl::free(frv, q);
    cl::sycl::free(fre, q);
    cl::sycl::free(gro, q);
    cl::sycl::free(gru, q);
    cl::sycl::free(grv, q);
    cl::sycl::free(gre, q);
    cl::sycl::free(wzDevice, q);
    cl::sycl::free(wz, q);
    cl::sycl::free(eps, q);
    cl::sycl::free(coef, q);
    cl::sycl::free(xx, q);
    cl::sycl::free(yy, q);
    cl::sycl::free(utm, q);
    cl::sycl::free(vtm, q);
    cl::sycl::free(ttm, q);
    cl::sycl::free(utmH, q);
    cl::sycl::free(vtmH, q);
    cl::sycl::free(ttmH, q);
#endif
    
    return 0;
}
