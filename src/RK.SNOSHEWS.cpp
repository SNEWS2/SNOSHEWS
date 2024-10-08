
#include "RK.h"

// *****************************************************************************

using std::complex;
using std::array;
using std::vector;

// ******************************************************************************

MATRIX<complex<double>,NF,NF> B(array<double,NY> y)
       { MATRIX<complex<double>,NF,NF> b;

         double cPsi1=cos(y[0]),sPsi1=sin(y[0]), cPsi2=cos(y[1]),sPsi2=sin(y[1]);
         double cPsi3=cos(y[2]),sPsi3=sin(y[2]), cPsi4=cos(y[3]),sPsi4=sin(y[3]), cPsi5=cos(y[4]),sPsi5=sin(y[4]);
         double cPsi6=cos(y[5]),sPsi6=sin(y[5]), cPsi7=cos(y[6]),sPsi7=sin(y[6]), cPsi8=cos(y[7]),sPsi8=sin(y[7]);

         b[0][2]=cPsi1 +I*sPsi1*cPsi2;
         sPsi1*=sPsi2;
         b[0][1]=sPsi1*cPsi3 +I*sPsi1*sPsi3*cPsi4;
         sPsi3*=sPsi4;
         b[0][0]=sPsi1*sPsi3*cPsi5 +I*sPsi1*sPsi3*sPsi5;

         b[1][2]=sPsi1*cPsi6 +I*sPsi1*sPsi6*cPsi7;
         sPsi1*=sPsi6*sPsi7;
         b[2][2]=sPsi1*cPsi8 +I*sPsi1*sPsi8;

         double d=1.-norm(b[0][2]);

         b[1][0]=(-y[8]*conj(b[0][1]*b[2][2])-b[1][2]*conj(b[0][2])*b[0][0])/d;
         b[1][1]=( y[8]*conj(b[0][0]*b[2][2])-b[1][2]*conj(b[0][2])*b[0][1])/d;

         b[2][0]=( y[8]*conj(b[1][2]*b[0][1])-b[2][2]*conj(b[0][2])*b[0][0])/d;
         b[2][1]=(-y[8]*conj(b[1][2]*b[0][0])-b[2][2]*conj(b[0][2])*b[0][1])/d;

         return b;
        }

// ********************** The Differential Equation ********************

void K(double r,double dr,vector<vector<array<double,NY> > > &Y,vector<vector<array<double,NY> > > &K)
          { MATRIX<complex<double>,NF,NF> VfMSW,VfMSWbar, dVfMSWdr,dVfMSWbardr;
            MATRIX<complex<double>,NF,NF> Hf,Hfbar, dHfdr,dHfbardr;
            MATRIX<complex<double>,NF,NF> UU,UUbar;

            array<double,NF> kk,kkbar, dkk,dkkbar;

            MATRIX<complex<double>,NF,NF> BB, WW;

            double rrho,drrhodr, YYe,dYYedr;

            MATRIX<double,8,10> JI;
            int i;

            MATRIX<complex<double>,NF,NF> Ha;
            MATRIX<complex<double>,NF,NF> HaB;
            array<double,3> phase;
            array<double,10> dvdr;

            // *************

            rrho=exp(lnrho(log(r)));
            drrhodr=rrho*lnrho.Derivative(log(r))/r;

            YYe=Ye(r); 
            dYYedr=Ye.Derivative(r);

            VfMSW[e][e]=Ve(rrho,YYe);
            VfMSW[mu][mu]=Vmu(rrho,YYe);
            VfMSW[tau][tau]=Vtau(rrho,YYe);

            VfMSWbar=-Conjugate(VfMSW);

            dVfMSWdr[e][e]=dVedr(rrho,drrhodr,YYe,dYYedr);
            dVfMSWdr[mu][mu]=dVmudr(rrho,drrhodr,YYe,dYYedr);
            dVfMSWdr[tau][tau]=dVtaudr(rrho,drrhodr,YYe,dYYedr);

            dVfMSWbardr=-Conjugate(dVfMSWdr);

            // *************

   	    // set up neutrino S matrices
            #pragma omp parallel for schedule(static) private(Hf,Hfbar,dHfdr,dHfbardr,BB,WW,UU,UUbar,kk,kkbar,dkk,dkkbar) firstprivate(Ha,HaB,dvdr,phase,JI)
            for(i=0;i<=NE-1;i++)
               { Hf=HfV[nu][i]+VfMSW;
                 dHfdr=dVfMSWdr;

		 kk=k(Hf);
                 dkk=deltak(kk);

	  	 UU=MixingMatrix(Hf,kk,dkk);

                 BB=B(Y[nu][i]);
                 WW=W(Y[nu][i]);

	         phase[0] = M_2PI*(Y[nu][i][9]-Y[nu][i][10]);
 		 phase[1] = M_2PI*(Y[nu][i][9]-Y[nu][i][11]);
		 phase[2] = M_2PI*(Y[nu][i][10]-Y[nu][i][11]);

		 Ha[0][1]=Ha[0][2]=Ha[1][2]=0.;
		 for(int j=0;j<=NF-2;j++)
                    { for(int k=j+1;k<=NF-1;k++)
                         { for(flavour f=e;f<=tau;f++)
                              { Ha[j][k]+= conj(UU[f][j])*dHfdr[f][f]*UU[f][k];}
		          } 
	    	     }

		 Ha[0][1] *= I*cgs::constants::hbarc/dkk[0]*exp(I*phase[0]); 	Ha[1][0] = conj(Ha[0][1]);  
		 Ha[0][2] *= I*cgs::constants::hbarc/dkk[1]*exp(I*phase[1]);  	Ha[2][0] = conj(Ha[0][2]);
		 Ha[1][2] *= I*cgs::constants::hbarc/dkk[2]*exp(I*phase[2]); 	Ha[2][1] = conj(Ha[1][2]);

		 // HaB = -I/cgs::constants::hbarc*Ha*BB[i];
                 HaB[0][0]=-I/cgs::constants::hbarc*( Ha[0][1]*BB[1][0] +Ha[0][2]*BB[2][0] );
                 HaB[0][1]=-I/cgs::constants::hbarc*( Ha[0][1]*BB[1][1] +Ha[0][2]*BB[2][1] );
                 HaB[0][2]=-I/cgs::constants::hbarc*( Ha[0][1]*BB[1][2] +Ha[0][2]*BB[2][2] );
                 HaB[1][2]=-I/cgs::constants::hbarc*( Ha[1][0]*BB[0][2] +Ha[1][2]*BB[2][2] );
                 HaB[2][2]=-I/cgs::constants::hbarc*( Ha[2][0]*BB[0][2] +Ha[2][1]*BB[1][2] );

                 dvdr[0]=real(HaB[0][2]);
                 dvdr[1]=imag(HaB[0][2]);
                 dvdr[2]=real(HaB[0][1]);
                 dvdr[3]=imag(HaB[0][1]);
                 dvdr[4]=real(HaB[0][0]);
                 dvdr[5]=imag(HaB[0][0]);
                 dvdr[6]=real(HaB[1][2]);
                 dvdr[7]=imag(HaB[1][2]);
                 dvdr[8]=real(HaB[2][2]);
                 dvdr[9]=imag(HaB[2][2]);

                 JI=JInverse(Y[nu][i]);

  		 for(int j=0;j<=4;j++){ K[nu][i][j]=0.; for(int k=j;k<=5;k++){ K[nu][i][j]+=JI[j][k]*dvdr[k];} K[nu][i][j]*=dr;}
                 for(int j=5;j<=7;j++){ K[nu][i][j]=0.; for(int k=j+1;k<=9;k++){ K[nu][i][j]+=JI[j][k]*dvdr[k];} K[nu][i][j]*=dr;}

		 K[nu][i][8]=0.;

		 K[nu][i][9]=(kk[0]/*+QQ[0]*/)*dr/M_2PI/cgs::constants::hbarc;
		 K[nu][i][10]=(kk[1]/*+QQ[1]*/)*dr/M_2PI/cgs::constants::hbarc;
		 K[nu][i][11]=(kk[2]/*+QQ[2]*/)*dr/M_2PI/cgs::constants::hbarc;

		 // ************* Antinu section

 		 Hfbar=HfV[antinu][i]+VfMSWbar;
 		 dHfbardr=dVfMSWbardr;

		 kkbar=k(Hfbar);
                 dkkbar=deltakbar(kkbar);

		 UUbar=MixingMatrix(Hfbar,kkbar,dkkbar);

                 BB=B(Y[antinu][i]);
                 WW=W(Y[antinu][i]);

		 phase[0]=M_2PI*(Y[antinu][i][9]-Y[antinu][i][10]);
		 phase[1]=M_2PI*(Y[antinu][i][9]-Y[antinu][i][11]);
		 phase[2]=M_2PI*(Y[antinu][i][10]-Y[antinu][i][11]);

		 Ha[0][1]=Ha[0][2]=Ha[1][2]=0.;
		 for(int j=0;j<=NF-2;j++)
                    { for(int k=j+1;k<=NF-1;k++)
                         { for(flavour f=e;f<=tau;f++)
                              { Ha[j][k]+=conj(UUbar[f][j]) * dHfbardr[f][f] * UUbar[f][k];} 
		          }  
		     }

		 Ha[0][1] *= I*cgs::constants::hbarc/dkkbar[0]*exp(I*phase[0]);	Ha[1][0] = conj(Ha[0][1]);  
		 Ha[0][2] *= I*cgs::constants::hbarc/dkkbar[1]*exp(I*phase[1]);	Ha[2][0] = conj(Ha[0][2]);
		 Ha[1][2] *= I*cgs::constants::hbarc/dkkbar[2]*exp(I*phase[2]);	Ha[2][1] = conj(Ha[1][2]);

		 //HaB=-I/cgs::constants::hbarc*Ha*BB;
                 HaB[0][0]=-I/cgs::constants::hbarc*( Ha[0][1]*BB[1][0] +Ha[0][2]*BB[2][0] );
                 HaB[0][1]=-I/cgs::constants::hbarc*( Ha[0][1]*BB[1][1] +Ha[0][2]*BB[2][1] );
                 HaB[0][2]=-I/cgs::constants::hbarc*( Ha[0][1]*BB[1][2] +Ha[0][2]*BB[2][2] );
                 HaB[1][2]=-I/cgs::constants::hbarc*( Ha[1][0]*BB[0][2] +Ha[1][2]*BB[2][2] );
                 HaB[2][2]=-I/cgs::constants::hbarc*( Ha[2][0]*BB[0][2] +Ha[2][1]*BB[1][2] );

                 dvdr[0]=real(HaB[0][2]);
                 dvdr[1]=imag(HaB[0][2]);
                 dvdr[2]=real(HaB[0][1]);
                 dvdr[3]=imag(HaB[0][1]);
                 dvdr[4]=real(HaB[0][0]);
                 dvdr[5]=imag(HaB[0][0]);
                 dvdr[6]=real(HaB[1][2]);
                 dvdr[7]=imag(HaB[1][2]);
                 dvdr[8]=real(HaB[2][2]);
                 dvdr[9]=imag(HaB[2][2]);

                 JI=JInverse(Y[antinu][i]);

  		 for(int j=0;j<=4;j++){ K[antinu][i][j]=0.; for(int k=j;k<=5;k++){ K[antinu][i][j]+=JI[j][k]*dvdr[k];} K[antinu][i][j]*=dr;}
                 for(int j=5;j<=7;j++){ K[antinu][i][j]=0.; for(int k=j+1;k<=9;k++){ K[antinu][i][j]+=JI[j][k]*dvdr[k];} K[antinu][i][j]*=dr;}

		 K[antinu][i][8]=0.; 

		 K[antinu][i][9]=(kkbar[0]/*+QQbar[0]*/)*dr/M_2PI/cgs::constants::hbarc;
		 K[antinu][i][10]=(kkbar[1]/*+QQbar[1]*/)*dr/M_2PI/cgs::constants::hbarc;
		 K[antinu][i][11]=(kkbar[2]/*+QQbar[2]*/)*dr/M_2PI/cgs::constants::hbarc;
                }//end for loop over i               
            } 


