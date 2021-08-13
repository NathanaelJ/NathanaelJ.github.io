
//==========================================================
//  2D Navier Stokes Equation Solver
//  Created      | Sylvain Laizet    | 2014 | Fortran
//  Translated   | Nathanael Jenkins | 2021 | C++
//  Parallelised | Nathanael Jenkins | 2021 | SYCL
//==========================================================
//  Version 3.6
//  Compile using makefile ONLY
//  Download makefile here: nathanaelj.github.io/PrivateSamples/Makefile
//  Last updated 13.08.2021



#include <iostream>     //  Printing (I/O)
#include <fstream>      //  File writing (I/O)
#include <cmath>        //  Math
#include <CL/sycl.hpp>      //  Parallelisation (SYCL)
#if DPC
    #include "dpc_common.hpp"   //  Used by DPCPP compiler
#endif

using namespace std;

//==========================================================
//==========================================================
//  Useful variables

//  'domain' and 'timesteps' to be defined by compiler preprocessor (makefile)
const int nx=domain, ny=domain, ns=3, nt=timesteps, imodulo=2500;
const double CFL=0.25;
//  nx x ny => Size of computational domain
//       nt => Number of time steps
//  imodulo => File write frequency

cl::sycl::device d = cl::sycl::device(deviceSelection);
cl::sycl::queue q(d);  //  Global SYCL queue
//  device defined by compiler (e.g. cl::sycl::gpu_selector{})

cl::sycl::event e, e1, e2, e3, e4, e5, e6, e7, e8, e9, e10, e11, e12, e13, e14, m1, s1, m2, s2, m3, s3, m4, s4, m5, s5, m6, s6;
//  events for dependencies





//==========================================================
//==========================================================
//  Functions

//==========================================================
//  Mean value of 2D field
void average(double* uuu, double &um, cl::sycl::event eDep, cl::sycl::event eDep2, cl::sycl::event &eSend){
    um = 0;
    //  Reduction scheme allows for parallel calculation of averages
    double* utm = cl::sycl::malloc_shared<double>(1, q);
    *utm = 0;
    eSend = q.submit([&](cl::sycl::handler &h) {
        h.depends_on(eDep);
        h.depends_on(eDep2);
#if DPC
        h.parallel_for(cl::sycl::nd_range<1>{nx*ny, sizeof(double)},
          cl::sycl::reduction(utm, plus<double>()),
          [=](cl::sycl::nd_item<1> idx, auto& utm)
          {
#else
        h.parallel_for(cl::sycl::nd_range<1>{nx*ny, sizeof(double)},
         cl::sycl::reduction(utm, cl::sycl::plus<double>()),
         [=](cl::sycl::nd_item<1> idx, auto& utm)
         {
#endif
            int i = idx.get_global_id(0);
            utm += uuu[i];
          });
    });
    um = *utm;
    um /= nx*ny;
    return;
}

//==========================================================
//  First derivative in x-direction
void derix(double *phi, double *dfi, double &xlx, cl::sycl::event dependent, cl::sycl::event &main, cl::sycl::event &sub){
    double udx=nx/(2*xlx);

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
    return;
}

//==========================================================
//  First derivative in y-direction
void deriy(double *phi, double *dfi, double &yly, cl::sycl::event dependent, cl::sycl::event &main, cl::sycl::event &sub){
    double udy=ny/(2*yly);

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
    return;
}
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

//==========================================================
//  Second derivative in x-direction
void derxx(double *phi, double *dfi, double &xlx, cl::sycl::event dependent, cl::sycl::event &main, cl::sycl::event &sub){
    double udx=pow(nx,2)/(pow(xlx,2));

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
    return;
}

//==========================================================
//  Second derivative in y-direction
void deryy(double *phi, double *dfi, double &yly, cl::sycl::event dependent, cl::sycl::event &main, cl::sycl::event &sub){
    double udy=pow(ny,2)/(pow(yly,2));

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
    return;
}

//==========================================================
//  4th order first derivative in x-direction
void derix4(double *phi, double *dfi, double &xlx){
    
    //  To be completed as an exercise
    return;
}

//==========================================================
//  4th order first derivative in y-direction
void deriy4(double *phi, double *dfi, double &yly){
    
    //  To be completed as an exercise
    return;
}

//==========================================================
//  4th order second derivative in x-direction
void derxx4(double *phi, double *dfi, double &xlx){
    
    //  To be completed as an exercise
    return;
}

//==========================================================
//  4th order second derivative in y-direction
void deryy4(double *phi, double *dfi, double &yly){
    
    //  To be completed as an exercise
    return;
}

//==========================================================
//  Right hand side calculations
void fluxx(double *uuu,double *vvv,double *rho,double *pre,double *tmp,double *rou,double *rov,double *roe,double *tb1,double *tb2,double *tb3,double *tb4,double *tb5,double *tb6,double *tb7,double *tb8,double *tb9,double *tba,double *tbb,double *fro,double *fru,double *frv,double *fre,double &xlx,double &yly,double &xmu,double &xba,double *eps,double &eta,double *ftp,double *scp,double &xkt){
        
#if fourOrder
    derix4(rou,tb1,xlx);
    deriy4(rov,tb2,yly);
#else
    derix(rou,tb1,xlx, e1, m1, s1);
    deriy(rov,tb2,yly, e1, m2, s2);
#endif

    auto e2 = q.submit([=] (auto &h) {
        h.depends_on(m1);
        h.depends_on(s1);
        h.depends_on(m2);
        h.depends_on(s2);
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            fro[i+nx*j]=-tb1[i+nx*j]-tb2[i+nx*j];
            tb1[i+nx*j]=rou[i+nx*j]*uuu[i+nx*j];
            tb2[i+nx*j]=rou[i+nx*j]*vvv[i+nx*j];
        });
    });

#if fourOrder
    derix4(pre,tb3,xlx);
    derix4(tb1,tb4,xlx);
    deriy4(tb2,tb5,yly);
    derxx4(uuu,tb6,xlx);
    deryy4(uuu,tb7,yly);
    derix4(vvv,tb8,xlx);
    deriy4(tb8,tb9,yly);
#else
    derix(pre,tb3,xlx, e1, m1, s1);
    derix(tb1,tb4,xlx, e2, m2, s2);
    deriy(tb2,tb5,yly, e2, m3, s3);
    derxx(uuu,tb6,xlx, e1, m4, s4);
    deryy(uuu,tb7,yly, e1, m5, s5);
    derix(vvv,tb8,xlx, e1, m6, s6);
    deriy2(tb8,tb9,yly, m6, s6, m6, s6);
#endif
    double utt=1.0/3.0;
    double qtt=4.0/3.0;

    auto e3 = q.submit([=] (auto &h) {
        h.depends_on(m1);
        h.depends_on(s1);
        h.depends_on(m2);
        h.depends_on(s2);
        h.depends_on(m3);
        h.depends_on(s3);
        h.depends_on(m4);
        h.depends_on(s4);
        h.depends_on(m5);
        h.depends_on(s5);
        h.depends_on(m6);
        h.depends_on(s6);
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            tba[i+nx*j]=xmu*(qtt*tb6[i+nx*j]+tb7[i+nx*j]+utt*tb9[i+nx*j]);
            fru[i+nx*j]=-tb3[i+nx*j]-tb4[i+nx*j]-tb5[i+nx*j]+tba[i+nx*j]-((eps[i+nx*j]/eta)*uuu[i+nx*j]);
            tb1[i+nx*j]=rou[i+nx*j]*vvv[i+nx*j];
            tb2[i+nx*j]=rov[i+nx*j]*vvv[i+nx*j];
        });
    });

#if fourOrder
    deriy4(pre,tb3,yly);
    derix4(tb1,tb4,xlx);
    deriy4(tb2,tb5,yly);
    derxx4(vvv,tb6,xlx);
    deryy4(vvv,tb7,yly);
    derix4(uuu,tb8,xlx);
    deriy4(tb8,tb9,yly);
#else
    deriy(pre,tb3,yly, e3, m1, s1);
    derix(tb1,tb4,xlx, e3, m2, s2);
    deriy(tb2,tb5,yly, e3, m3, s3);
    derxx(vvv,tb6,xlx, e3, m4, s4);
    deryy(vvv,tb7,yly, e3, m5, s5);
    derix(uuu,tb8,xlx, e3, m6, s6);
    deriy2(tb8,tb9,yly, m6, s6, m6, s6);
#endif

    auto e4 = q.submit([=] (auto &h) {
        h.depends_on(m1);
        h.depends_on(s1);
        h.depends_on(m2);
        h.depends_on(s2);
        h.depends_on(m3);
        h.depends_on(s3);
        h.depends_on(m4);
        h.depends_on(s4);
        h.depends_on(m5);
        h.depends_on(s5);
        h.depends_on(m6);
        h.depends_on(s6);
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            tbb[i+nx*j]=xmu*(tb6[i+nx*j]+qtt*tb7[i+nx*j]+utt*tb9[i+nx*j]);
            frv[i+nx*j]=-tb3[i+nx*j]-tb4[i+nx*j]-tb5[i+nx*j]+tbb[i+nx*j]-(eps[i+nx*j]/eta)*vvv[i+nx*j];
        });
    });

#if fourOrder
    derix4(scp,tb1,xlx);
    deriy4(scp,tb2,yly);
    derxx4(scp,tb3,xlx);
    deryy4(scp,tb4,yly);
#else
    derix(scp,tb1,xlx, e3, m1, s1);
    deriy(scp,tb2,yly, e3, m2, s2);
    derxx(scp,tb3,xlx, e4, m3, s3);
    deryy(scp,tb4,yly, e4, m4, s4);
#endif

    auto e5 = q.submit([=] (auto &h) {
        h.depends_on(m1);
        h.depends_on(s1);
        h.depends_on(m2);
        h.depends_on(s2);
        h.depends_on(m3);
        h.depends_on(s3);
        h.depends_on(m4);
        h.depends_on(s4);
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            ftp[i+nx*j]=-uuu[i+nx*j]*tb1[i+nx*j]-vvv[i+nx*j]*tb2[i+nx*j]+xkt*(tb3[i+nx*j]+tb4[i+nx*j])-(eps[i+nx*j]/eta)*scp[i+nx*j];
        });
    });

#if fourOrder
    derix4(uuu,tb1,xlx);
    deriy4(vvv,tb2,yly);
    deriy4(uuu,tb3,yly);
    derix4(vvv,tb4,xlx);
#else
    derix(uuu,tb1,xlx, e5, m1, s1);
    deriy(vvv,tb2,yly, e5, m2, s2);
    deriy(uuu,tb3,yly, e5, m3, s3);
    derix(vvv,tb4,xlx, e5, m4, s4);
#endif
    double dmu=(2.0/3.0)*xmu;

    auto e6 = q.submit([=] (auto &h) {
        h.depends_on(m1);
        h.depends_on(s1);
        h.depends_on(m2);
        h.depends_on(s2);
        h.depends_on(m3);
        h.depends_on(s3);
        h.depends_on(m4);
        h.depends_on(s4);
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

#if fourOrder
    derix4(tb1,tb5,xlx);
    derix4(tb2,tb6,xlx);
    deriy4(tb3,tb7,yly);
    deriy4(tb4,tb8,yly);
    derxx4(tmp,tb9,xlx);
    deryy4(tmp,tba,yly);
#else
    derix(tb1,tb5,xlx, e6, m1, s1);
    derix(tb2,tb6,xlx, e6, m2, s2);
    deriy(tb3,tb7,yly, e6, m3, s3);
    deriy(tb4,tb8,yly, e6, m4, s4);
    derxx(tmp,tb9,xlx, e5, m5, s5);
    deryy(tmp,tba,yly, e5, m6, s6);
#endif

    e7 = q.submit([=] (auto &h) {
        h.depends_on(m1);
        h.depends_on(s1);
        h.depends_on(m2);
        h.depends_on(s2);
        h.depends_on(m3);
        h.depends_on(s3);
        h.depends_on(m4);
        h.depends_on(s4);
        h.depends_on(m5);
        h.depends_on(s5);
        h.depends_on(m6);
        h.depends_on(s6);
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int i = idx[1];
            int j = idx[0];
            fre[i+nx*j]=fre[i+nx*j]-tb5[i+nx*j]-tb6[i+nx*j]-tb7[i+nx*j]-tb8[i+nx*j]+xba*(tb9[i+nx*j]+tba[i+nx*j]);
        });
    });

    return;
}

//==========================================================
//  Runge-Kutta time advancement
void rkutta(double *rho,double *rou,double *rov,double *roe,double *fro,double *gro,double *fru,double *gru,double *frv,double *grv,double *fre,double *gre,double *ftp,double *gtp,double &dlt,double *coef,double *scp,int &k){
    
    //  To be completed as an exercise
    return;
}

//==========================================================
//  Adams-Bashforth time advancement
void adams(double *rho,double *rou,double *rov,double *roe,double *fro,double *gro,double *fru,double *gru,double *frv,double *grv,double *fre,double *gre,double *ftp,double *gtp,double *scp,double &dlt){
    
    double ct1=1.5*dlt;
    double ct2=0.5*dlt;

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
//    double ct4=yly/2.0;
    double ct6=(gma-1)/gma;
//    double y=-ct4;
//    double x=0.0;
    eta=0.1;
    eta=eta/2.0;
    double radius=d/2.0;
    xkt=xba/(chp*roi);
    double pi=acos(-1.0);
        
    double rSquared = pow(radius, 2);
    q.submit([=] (auto &h) {
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
    q.submit([=] (auto &g) {
        g.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
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
    q.wait();
    
    return;
}

//==========================================================
//  Update u, v, p, and t each time step
void etatt(double *uuu,double *vvv,double *rho,double *pre,double *tmp,double *rou,double *rov,double *roe,double &gma,double &chp){
    double ct7=gma-1.0;
    double ct8=gma/(gma-1.0);
    e = q.submit([=] (auto &h) {
        h.depends_on(e8);
        h.depends_on(e9);
        h.depends_on(e10);
        h.depends_on(e11);
        h.depends_on(e12);
        h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
            int j = idx[0];
            int i = idx[1];
            uuu[i+nx*j]=rou[i+nx*j]/rho[i+nx*j];
            vvv[i+nx*j]=rov[i+nx*j]/rho[i+nx*j];
            pre[i+nx*j]=ct7*(roe[i+nx*j]-(0.5*((rou[i+nx*j]*uuu[i+nx*j])+(rov[i+nx*j]*vvv[i+nx*j]))));
            tmp[i+nx*j]=ct8*pre[i+nx*j]/(rho[i+nx*j]*chp);
        });
    });
    return;
}




//==========================================================
//==========================================================
//  Main Program

int main(){
    //==========================================================
    //  Variable definitions
    const int nf=3, mx=nf*nx, my=nf*ny;
    double xlx,yly,dlx,dx,xmu,xkt;
    double xba,gma,chp,eta,uu0,dlt,x,y,dy;
    double um,vm,tm,um0,vm0,tm0;
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
    auto wz = cl::sycl::malloc_shared<double>(nx*ny, q);
    auto eps = cl::sycl::malloc_device<double>(nx*ny, q);
    auto coef = cl::sycl::malloc_device<double>(2*ns, q);
    auto xx = cl::sycl::malloc_host<double>(mx, q);
    auto yy = cl::sycl::malloc_host<double>(my, q);
        
    //==========================================================
    // Setup

    initl(uuu,vvv,rho,eee,pre,tmp,rou,rov,roe,xlx,yly,xmu,xba,
          gma,chp,dlx,eta,eps,scp,xkt,uu0);
    dx=xlx/nx;
    dy=yly/ny;
    dlt=CFL*dlx;

    average(uuu,um0, e, e, m1);
    average(vvv,vm0, e, e, m2);
    average(scp,tm0, e, e, m3);
    
    // Print to screen
    cout << "\n\x1B[32m\e[1m2D Navier-Stokes Solver (Using Explicit USM)\e[0m\033[0m\t\t" << endl;
    cout << "\x1B[32mThe time step of the simulation is " << dlt << "\e[0m\033[0m\t\t" << endl;
    cout << "\x1B[32mParallelism activated" << endl;
    cout << "Using " << d.get_info<cl::sycl::info::device::name>() << "\e[0m\033[0m\t\t\n";
    cout << "====================================================================================" << endl;
    printf("  iter |                     uuu |                     vvv |                     scp\n");
    e = q.submit([&] (cl::sycl::handler &h) {
        h.depends_on(m1);
        h.depends_on(m2);
        h.depends_on(m3);
        h.single_task([=] () {
            printf("     0 % 25.16e % 25.16e % 25.16e \n", um0, vm0, tm0);
        });
    });

    //==========================================================
    // Time loop
    for(int n=1; n<=nt; n++){
#if ITEMP
        // Adams-bashforth temporal method
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
        for(int k=1; k<=ns; k++){
            // Compute RHS
            fluxx(uuu,vvv,rho,pre,tmp,rou,rov,roe,tb1,tb2,
                  tb3,tb4,tb5,tb6,tb7,tb8,tb9,tba,tbb,fro,fru,frv,
                  fre,xlx,yly,xmu,xba,eps,eta,ftp,scp,xkt);
            // Time advancement
            rkutta(rho,rou,rov,roe,fro,gro,fru,gru,frv,grv,fre,
                   gre,ftp,gtp,dlt,coef,scp,k);
            // Update fields
            etatt(uuu,vvv,rho,pre,tmp,rou,rov,roe,gma,chp);
        }
#endif

        //==========================================================
        // Save snapshots
        cout << "\e[0m\033 Iteration " << n << "   \e\n[F";
        if (n%imodulo==0){
            // Generate results for gnuplot
            cout << "\e[0m\033[0m\x1B[34m\e[1mWriting File...\e[0m\033[0m\t\t\e[F\e[2m" << endl;
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

            // Vorticity calculation
            derix(vvv,tvv,xlx, e, m1, s1);
            deriy(uuu,tuu,yly, e, m2, s2);

            q.submit([=] (auto &h) {
                h.depends_on(m1);
                h.depends_on(s1);
                h.depends_on(m2);
                h.depends_on(s2);
                h.parallel_for(cl::sycl::range{ ny, nx }, [=](cl::sycl::id<2> idx){
                    int j = idx[0];
                    int i = idx[1];
                    wz[i+nx*j]=tvv[i+nx*j]-tuu[i+nx*j];
                });
            }).wait();

            // Generate file
            int temp = n/imodulo;
            string filename = "vort";
            filename += std::to_string(temp);
            fstream nfichier(filename, ios::out | ios::trunc);
            for(int j=0; j<my; ++j){
                for(int i=0; i<mx; ++i){
                    int ii = i%nx;
                    int jj = j%ny;
                    if (nfichier.is_open()){
                        nfichier << xx[i] << " " << yy[j] << " " << wz[ii+nx*jj] << endl;
                    }
                    else {
                        cout << "\a" << endl;
                        cerr << "\x1B[31m\e[1mUnable to open file\e[0m\033[0m\t\t" << endl;
                        exit(-2);
                    }
                }
                nfichier << "\n";
            }
            nfichier.close();
        }
        
//         Compute field averages
        average(uuu,um, e, e14, m1);
        average(vvv,vm, e, e14, m2);
        average(scp,tm, e, e14, m3);

        // Print average values to screen
        e14 = q.submit([&] (cl::sycl::handler &h) {
            h.depends_on(m1);
            h.depends_on(m2);
            h.depends_on(m3);
            h.single_task([=] () {
                printf("%6i % 25.16e % 25.16e % 25.16e \n\e[0m", n, um, vm, tm);
            });
        });

    }
    // End of time loop
    
    // Print to screen & error/NaN handling
    cout << "\e[0m\033 ====================================================================================" << endl;
    if (isnan(um)) {
        // Error returned if uuu field contains any NaN values
        cerr << "\a\x1B[31mSimulation complete. NaN in result!\e[0m\033[0m\t\t" << endl;
    }
    else {
        cout << "\x1B[32mDone!\e[0m\033[0m\t\t\a" << endl;
    }
    
    //  Deallocate memory to prevent leaks
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
    cl::sycl::free(wz, q);
    cl::sycl::free(eps, q);
    cl::sycl::free(coef, q);
    cl::sycl::free(xx, q);
    cl::sycl::free(yy, q);
    
    return 0;
}
