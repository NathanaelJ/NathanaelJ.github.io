//==========================================================
//  2D Navier Stokes Equation Solver
//  Created      | Sylvain Laizet    | 2014 | Fortran
//  Translated   | Nathanael Jenkins | 2021 | C++
//  Parallelised | Nathanael Jenkins |      | hipSYCL
//==========================================================
//  Version 1.0
//  Basic C++ code, no implementation of hipSYCL
//  Compile using g++: 'g++ -O3 2DSolver.cpp -o run && ./run'

// NOTE - a bug is present in this code that generates invalid results

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

const int nx=200, ny=200, ns=3;



//==========================================================
//==========================================================
//  Functions

//==========================================================
//  Mean value of 2D field
void average(double uuu[nx][ny], double &um){
    um=0;
    for(int j=0; j<ny; j++){
        for(int i=0; i<nx; i++){
            um += uuu[i][j];
        }
    }
    um/=(nx*ny);
    return;
}

//==========================================================
//  First derivative in x-direction
void derix(double phi[nx][ny], double dfi[nx][ny], double &xlx){
    
    double udx=nx/(2*xlx);
    
    for(int j=0; j<ny; j++){
        dfi[0][j]=udx*(phi[1][j]-phi[nx-1][j]);
        for(int i=1; i<nx-1; i++){
            dfi[i][j]=udx*(phi[i+1][j]-phi[i-1][j]);
        }
        dfi[nx-1][j]=udx*(phi[0][j]-phi[nx-2][j]);
    }
    
    return;
}

//==========================================================
//  First derivative in y-direction
void deriy(double phi[nx][ny], double dfi[nx][ny], double &yly){
    double udy=ny/(2*yly);
    for(int j=1; j<ny-1; j++){
        for(int i=0; i<nx; i++){
            dfi[i][j]=udy*(phi[i][j+1]-phi[i][j-1]);
        }
    }
    for(int i=0; i<nx; i++){
        dfi[i][0]=udy*(phi[i][1]-phi[i][ny-1]);
        dfi[i][ny-1]=udy*(phi[i][0]-phi[i][ny-2]);
    }
    return;
}

//==========================================================
//  Second derivative in x-direction
void derxx(double phi[nx][ny], double dfi[nx][ny], double &xlx){
    double udx=pow(nx,2)/(pow(xlx,2));
    for(int j=0; j<ny; j++){
        dfi[0][j]=udx*(phi[1][j]-(phi[0][j]+phi[0][j])+phi[nx-1][j]);
        for(int i=1; i<nx-1; i++){
            dfi[i][j]=udx*(phi[i+1][j]-(phi[i][j]+phi[i][j])+phi[i-1][j]);
        }
        dfi[nx-1][j]=udx*(phi[0][j]-(phi[nx-1][j]+phi[nx-1][j])+phi[nx-2][j]);
    }
    return;
}

//==========================================================
//  Second derivative in y-direction
void deryy(double phi[nx][ny], double dfi[nx][ny], double &yly){
    double udy=pow(ny,2)/(pow(yly,2));
    for(int j=1; j<ny-1; j++){
        for(int i=0; i<nx; i++){
            dfi[i][j]=udy*(phi[i][j+1]-(phi[i][j]+phi[i][j])+phi[i][j-1]);
        }
    }
    for(int i=0; i<nx; i++){
        dfi[i][0]=udy*(phi[i][1]-(phi[i][0]+phi[i][0])+phi[i][ny-1]);
        dfi[i][ny-1]=udy*(phi[i][0]-(phi[i][ny-1]+phi[i][ny-1])+phi[i][ny-2]);
    }
    return;
}

//==========================================================
//  4th order first derivative in x-direction
void derix4(double phi[nx][ny], double dfi[nx][ny], double &xlx){
    
    //  To be completed as an exercise
    return;
}

//==========================================================
//  4th order first derivative in y-direction
void deriy4(double phi[nx][ny], double dfi[nx][ny], double &yly){
    
    //  To be completed as an exercise
    return;
}

//==========================================================
//  4th order second derivative in x-direction
void derxx4(double phi[nx][ny], double dfi[nx][ny], double &xlx){
    
    //  To be completed as an exercise
    return;
}

//==========================================================
//  4th order second derivative in y-direction
void deryy4(double phi[nx][ny], double dfi[nx][ny], double &yly){
    
    //  To be completed as an exercise
    return;
}

//==========================================================
//  Right hand side calculations
void fluxx(double uuu[nx][ny],double vvv[nx][ny],double rho[nx][ny],double pre[nx][ny],double tmp[nx][ny],double rou[nx][ny],double rov[nx][ny],double roe[nx][ny],double tb1[nx][ny],double tb2[nx][ny],double tb3[nx][ny],double tb4[nx][ny],double tb5[nx][ny],double tb6[nx][ny],double tb7[nx][ny],double tb8[nx][ny],double tb9[nx][ny],double tba[nx][ny],double tbb[nx][ny],double fro[nx][ny],double fru[nx][ny],double frv[nx][ny],double fre[nx][ny],double &xlx,double &yly,double &xmu,double &xba,double eps[nx][ny],double &eta,double ftp[nx][ny],double scp[nx][ny],double &xkt){
    derix(rou,tb1,xlx);
    deriy(rov,tb2,yly);
    for(int j=0; j<ny; j++){
        for(int i=0; i<nx; i++){
            fro[i][j]=-tb1[i][j]-tb2[i][j];
        }
    }
    
    for(int j=0; j<ny; j++){
        for(int i=0; i<nx; i++){
            tb1[i][j]=rou[i][j]*uuu[i][j];
            tb2[i][j]=rou[i][j]*vvv[i][j];
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
    for(int j=0; j<ny; j++){
        for(int i=0; i<nx; i++){
            tba[i][j]=xmu*(qtt*tb6[i][j]+tb7[i][j]+utt*tb9[i][j]);
            fru[i][j]=-tb3[i][j]-tb4[i][j]-tb5[i][j]+tba[i][j]-((eps[i][j]/eta)*uuu[i][j]);
        }
    }

    for(int j=0; j<ny; j++){
        for(int i=0; i<nx; i++){
            tb1[i][j]=rou[i][j]*vvv[i][j];
            tb2[i][j]=rov[i][j]*vvv[i][j];
        }
    }

    deriy(pre,tb3,yly);
    derix(tb1,tb4,xlx);
    deriy(tb2,tb5,yly);
    derxx(vvv,tb6,xlx);
    deryy(vvv,tb7,yly);
    derix(uuu,tb8,xlx);
    deriy(tb8,tb9,yly);
    for(int j=0; j<ny; j++){
        for(int i=0; i<nx; i++){
            tbb[i][j]=xmu*(tb6[i][j]+qtt*tb7[i][j]+utt*tb9[i][j]);
            frv[i][j]=-tb3[i][j]-tb4[i][j]-tb5[i][j]+tbb[i][j]-(eps[i][j]/eta)*vvv[i][j];
       }
    }

    derix(scp,tb1,xlx);
    deriy(scp,tb2,yly);
    derxx(scp,tb3,xlx);
    deryy(scp,tb4,yly);
    for(int j=0; j<ny; j++){
        for(int i=0; i<nx; i++){
            ftp[i][j]=-uuu[i][j]*tb1[i][j]-vvv[i][j]*tb2[i][j]+xkt*(tb3[i][j]+tb4[i][j])-(eps[i][j]/eta)*scp[i][j];
        }
    }

    derix(uuu,tb1,xlx);
    deriy(vvv,tb2,yly);
    deriy(uuu,tb3,yly);
    derix(vvv,tb4,xlx);
    double dmu=(2.0/3.0)*xmu;
    for(int j=0; j<ny; j++){
        for(int i=0; i<nx; i++){
          fre[i][j]=xmu*(uuu[i][j]*tba[i][j]+vvv[i][j]*tbb[i][j])+(xmu+xmu)*(tb1[i][j]*tb1[i][j]+tb2[i][j]*tb2[i][j])-dmu*(tb1[i][j]+tb2[i][j])*(tb1[i][j]+tb2[i][j])+xmu*(tb3[i][j]+tb4[i][j])*(tb3[i][j]+tb4[i][j]);
        }
    }
    for(int j=0; j<ny; j++){
        for(int i=0; i<nx; i++){
            tb1[i][j]=roe[i][j]*uuu[i][j];
            tb2[i][j]=pre[i][j]*uuu[i][j];
            tb3[i][j]=roe[i][j]*vvv[i][j];
            tb4[i][j]=pre[i][j]*vvv[i][j];
        }
    }

    derix(tb1,tb5,xlx);
    derix(tb2,tb6,xlx);
    deriy(tb3,tb7,yly);
    deriy(tb4,tb8,yly);
    derxx(tmp,tb9,xlx);
    deryy(tmp,tba,yly);
    for(int j=0; j<ny; j++){
        for(int i=0; i<nx; i++){
            fre[i][j]=fre[i][j]-tb5[i][j]-tb6[i][j]-tb7[i][j]-tb8[i][j]+xba*(tb9[i][j]+tba[i][j]);
        }
    }

    return;
}

//==========================================================
//  Runge-Kutta time advancement
void rkutta(double rho[nx][ny],double rou[nx][ny],double rov[nx][ny],double roe[nx][ny],double fro[nx][ny],double gro[nx][ny],double fru[nx][ny],double gru[nx][ny],double frv[nx][ny],double grv[nx][ny],double fre[nx][ny],double gre[nx][ny],double ftp[nx][ny],double gtp[nx][ny],double &dlt,double coef[2][ns],double scp[nx][ny],int &k){
    
    //  To be completed as an exercise
    return;
}

//==========================================================
//  Adams-Bashforth time advancement
void adams(double rho[nx][ny],double rou[nx][ny],double rov[nx][ny],double roe[nx][ny],double fro[nx][ny],double gro[nx][ny],double fru[nx][ny],double gru[nx][ny],double frv[nx][ny],double grv[nx][ny],double fre[nx][ny],double gre[nx][ny],double ftp[nx][ny],double gtp[nx][ny],double scp[nx][ny],double &dlt){
    
    double ct1=1.5*dlt;
    double ct2=0.5*dlt;
    for(int j=0; j<ny; j++){
        for(int i=0; i<nx; i++){
            rho[i][j]+=(ct1*fro[i][j])-(ct2*gro[i][j]);
            gro[i][j]=fro[i][j];
            rou[i][j]+=(ct1*fru[i][j])-(ct2*gru[i][j]);
            gru[i][j]=fru[i][j];
            rov[i][j]+=(ct1*frv[i][j])-(ct2*grv[i][j]);
            grv[i][j]=frv[i][j];
            roe[i][j]+=(ct1*fre[i][j])-(ct2*gre[i][j]);
            gre[i][j]=fre[i][j];
            scp[i][j]+=(ct1*ftp[i][j])-(ct2*gtp[i][j]);
            gtp[i][j]=ftp[i][j];
       }
    }

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
void initl(double uuu[nx][ny],double vvv[nx][ny],double rho[nx][ny],double eee[nx][ny],double pre[nx][ny],double tmp[nx][ny],double rou[nx][ny],double rov[nx][ny],double roe[nx][ny],double &xlx,double &yly,double &xmu,double &xba,double &gma,double &chp,double &dlx,double &eta,double eps[nx][ny],double scp[nx][ny],double &xkt,double &uu0){
    double roi,cci,d,tpi,chv;
    
    param(xlx,yly,xmu,xba,gma,chp,roi,cci,d,tpi,chv,uu0);
    
    dlx=xlx/nx;
    double dly=yly/ny;
    double ct4=yly/2.0;
    double ct6=(gma-1)/gma;
    double y=-ct4;
    double x=0.0;
    eta=0.1;
    eta=eta/2.0;
    double radius=d/2.0;
    xkt=xba/(chp*roi);
    double pi=acos(-1.0);
    for(int j=0; j<ny; j++){
        for(int i=0; i<nx; i++){
            if ((pow((i+1)*dlx-xlx/2.0, 2)+pow((j+1)*dly-yly/2.0,2)) < pow(radius,2)){
                eps[i][j]=1.0;
            }
            else{
                eps[i][j]=0.0;
            }
        }
    }
    for(int j=0; j<ny; j++){
        for(int i=0; i<nx; i++){
            uuu[i][j]=uu0;
            vvv[i][j]=0.01*(sin(4*pi*(i+1)*dlx/xlx)+sin(7.0*pi*(i+1)*dlx/xlx))*exp(-pow((j+1)*dly-yly/2.0, 2));
            tmp[i][j]=tpi;
            eee[i][j]=chv*tmp[i][j]+0.5*(uuu[i][j]*uuu[i][j]+vvv[i][j]*vvv[i][j]);
            rho[i][j]=roi;
            pre[i][j]=rho[i][j]*ct6*chp*tmp[i][j];
            rou[i][j]=rho[i][j]*uuu[i][j];
            rov[i][j]=rho[i][j]*vvv[i][j];
            roe[i][j]=rho[i][j]*eee[i][j];
            scp[i][j]=1.0;
            x+=dlx;
        }
        y+=dly;
    }
    
    return;
}

//==========================================================
//  Update u, v, p, and t each time step
void etatt(double uuu[nx][ny],double vvv[nx][ny],double rho[nx][ny],double pre[nx][ny],double tmp[nx][ny],double rou[nx][ny],double rov[nx][ny],double roe[nx][ny],double &gma,double &chp){
    double ct7=gma-1.0;
    double ct8=gma/(gma-1.0);
    for(int j=0; j<ny; j++){
        for(int i=0; i<nx; i++){
            uuu[i][j]=rou[i][j]/rho[i][j];
            vvv[i][j]=rov[i][j]/rho[i][j];
            pre[i][j]=ct7*(roe[i][j]-(0.5*((rou[i][j]*uuu[i][j])+(rov[i][j]*vvv[i][j]))));
            tmp[i][j]=ct8*pre[i][j]/(rho[i][j]*chp);
        }
    }

    return;
}



//==========================================================
//==========================================================
//  Main Program

int main(){
    //==========================================================
    //  Variable definitions
    const int nt=1000, nf=3, mx=nf*nx, my=nf*ny;
    int itemp, imodulo;
    double uuu[nx][ny],vvv[nx][ny],rho[nx][ny],eee[nx][ny],pre[nx][ny];
    double tmp[nx][ny],rou[nx][ny],rov[nx][ny],wz[nx][ny],tuu[nx][ny];
    double tvv[nx][ny],ftp[nx][ny],roe[nx][ny],tb1[nx][ny],tb2[nx][ny];
    double tb3[nx][ny],tb4[nx][ny],tb5[nx][ny],tb6[nx][ny],tb7[nx][ny];
    double tb8[nx][ny],tb9[nx][ny],gtp[nx][ny],scp[nx][ny],tba[nx][ny];
    double tbb[nx][ny],fro[nx][ny],fru[nx][ny],frv[nx][ny],fre[nx][ny];
    double gro[nx][ny],gru[nx][ny],grv[nx][ny],gre[nx][ny];
    double eps[nx][ny];
    double tf[mx][my];
    double coef[2][ns];
    double xx[mx];
    double yy[my];
    double xlx,yly,CFL,dlx,dx,xmu,xkt,um0,vm0,tm0;
    double xba,gma,chp,eta,uu0,dlt,um,vm,tm,x,y,dy;
    
    //==========================================================
    // Setup
    imodulo = 2500;
    itemp = 1;
    CFL = 0.25;
    
    initl(uuu,vvv,rho,eee,pre,tmp,rou,rov,roe,xlx,yly,xmu,xba,
          gma,chp,dlx,eta,eps,scp,xkt,uu0);
    dx=xlx/nx;
    dy=yly/ny;
    dlt=CFL*dlx;
    cout << "The time step of the simulation is " << dlt << endl;
    average(uuu,um0);
    average(vvv,vm0);
    average(scp,tm0);
    printf(" 0     % 25.16e % 25.16e % 25.16e \n", um0, vm0, tm0);

    //==========================================================
    // Time loop
    for(int n=1; n<=nt; n++){
        switch (itemp){
            case 1:
                fluxx(uuu,vvv,rho,pre,tmp,rou,rov,roe,tb1,tb2,
                      tb3,tb4,tb5,tb6,tb7,tb8,tb9,tba,tbb,fro,fru,frv,
                      fre,xlx,yly,xmu,xba,eps,eta,ftp,scp,xkt);
                adams(rho,rou,rov,roe,fro,gro,fru,gru,frv,grv,fre,
                      gre,ftp,gtp,scp,dlt);
                etatt(uuu,vvv,rho,pre,tmp,rou,rov,roe,gma,chp);
                break;
            case 2:
                for(int k=1; k<=ns; k++){
                    fluxx(uuu,vvv,rho,pre,tmp,rou,rov,roe,tb1,tb2,
                          tb3,tb4,tb5,tb6,tb7,tb8,tb9,tba,tbb,fro,fru,frv,
                          fre,xlx,yly,xmu,xba,eps,eta,ftp,scp,xkt);
                    rkutta(rho,rou,rov,roe,fro,gro,fru,gru,frv,grv,fre,
                           gre,ftp,gtp,dlt,coef,scp,k);
                    etatt(uuu,vvv,rho,pre,tmp,rou,rov,roe,gma,chp);
                }
                break;
            default:
                cerr << "ERROR! itemp is not valid." << endl;
                cout << "Use itemp=1 for 2nd order adams method" << endl
                     << "Use itemp=2 for 3rd order RK method" << endl;
                exit(-1);
                break;
        }

        //==========================================================
        // Save snapshots
        if (n%imodulo==0){
            x=0;
            for(int i=0; i<mx; i++){
                xx[i]=x;
                x+=dx;
            }
            y=0;
            for(int j=0; j<my; j++){
                yy[j]=y;
                y+=dy;
            }
            derix(vvv,tvv,xlx);
            deriy(uuu,tuu,yly);
            for(int j=0; j<=ny; j++){
                for(int i=0; i<=nx; i++){
                    wz[i][j]=tvv[i][j]-tuu[i][j];
                }
            }
            for(int ni=1; ni<=nf; ni++){
                for(int nj=1; nj<=nf; nj++){
                    for(int j=0; j<ny; j++){
                        for(int i=0; i<nx; i++){
                            tf[i+(ni-1)*nx][j+(nj-1)*ny]=wz[i][j];
                        }
                    }
                }
            }

            int temp = n/imodulo;
            string filename = "vort000";
            filename += std::to_string(temp);
            fstream nfichier(filename, ios::out | ios::trunc);
            for(int j=0; j<my; j++){
                for(int i=0; i<mx; i++){
                    if (nfichier.is_open()){
                        nfichier << xx[i] << " " << yy[j] << " " << tf[i][j] << endl;
                    }
                    else {
                        cerr << "Unable to open file" << endl;
                        exit(-1);
                    }
                }
                nfichier << "\n";
            }
            nfichier.close();
        }
        
        average(uuu,um);
        average(vvv,vm);
        average(scp,tm);
        printf("%6i % 25.16e % 25.16e % 25.16e \n", n, um, vm, tm);
    }
    return 0;
}
