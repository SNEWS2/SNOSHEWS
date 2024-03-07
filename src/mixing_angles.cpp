
#include "mixing_angles.h"

// *********************************************************************

using std::complex;
using std::array;
using std::norm;
using std::real;
using std::imag;

// *********************************************************************
// *********************************************************************
// *********************************************************************

MATRIX<complex<double>,NF,NF> MixingMatrix(MATRIX<complex<double>,NF,NF> Hf,array<double,NF> k,array<double,NF> dk)
       { MATRIX<complex<double>,NF,NF> u;

         double d;
         array<double,NF> den2;

         for(int j=0;j<=NF-1;j++)
            { if(j==0){ d=dk[0]*dk[1];}  // first column 
              if(j==1){ d=-dk[0]*dk[2];} // second column
              if(j==2){ d=dk[1]*dk[2];}  // third column

              den2[e]=real(C<e,e>(Hf,k[j]))*d;
              den2[mu]=real(C<mu,mu>(Hf,k[j]))*d;
              den2[tau]=real(C<tau,tau>(Hf,k[j]))*d;

              //if(den2[e]>=den2[mu] && den2[e]>=den2[tau]){ u[e][j]=C<e,e>(Hf,k[j])/sqrt(den2[e]);       u[mu][j]=C<e,mu>(Hf,k[j])/sqrt(den2[e]);     u[tau][j]=C<e,tau>(Hf,k[j])/sqrt(den2[e]);}
              //if(den2[mu]>=den2[e] && den2[mu]>=den2[tau]){ u[e][j]=C<mu,e>(Hf,k[j])/sqrt(den2[mu]);    u[mu][j]=C<mu,mu>(Hf,k[j])/sqrt(den2[mu]);   u[tau][j]=C<mu,tau>(Hf,k[j])/sqrt(den2[mu]);}
              //if(den2[tau]>=den2[e] && den2[tau]>=den2[mu]){ u[e][j]=C<tau,e>(Hf,k[j])/sqrt(den2[tau]); u[mu][j]=C<tau,mu>(Hf,k[j])/sqrt(den2[tau]); u[tau][j]=C<tau,tau>(Hf,k[j])/sqrt(den2[tau]);}
              // set the element in the e (top) row to be pure real
              /*if(j==0 || j==1 || j==2)*/{ u[e][j]=C<e,e>(Hf,k[j])/sqrt(den2[e]); u[mu][j]=C<e,mu>(Hf,k[j])/sqrt(den2[e]); u[tau][j]=C<e,tau>(Hf,k[j])/sqrt(den2[e]);}
              // set the element in the tau (bottom) row to be pure real for the 3rd column
              //if(j==2){ u[e][j]=C<tau,e>(Hf,k[j])/sqrt(den2[tau]); u[mu][j]=C<tau,mu>(Hf,k[j])/sqrt(den2[tau]); u[tau][j]=C<tau,tau>(Hf,k[j])/sqrt(den2[tau]);}
            }
       
        return u;
       }

void Evaluate_UV(void) 
       { UV[nu][0][0] = c12V*c13V * exp(I*etaV[0]);
         UV[nu][0][1] = s12V*c13V * exp(I*etaV[1]);
         UV[nu][0][2] = s13V * exp(I*(etaV[2]-deltaV));

         UV[nu][1][0] = -(s12V*c23V + c12V*s13V*s23V*exp(I*deltaV)) * exp(I*etaV[0]);
         UV[nu][1][1] =  (c12V*c23V - s12V*s13V*s23V*exp(I*deltaV)) * exp(I*etaV[1]);
         UV[nu][1][2] =  c13V*s23V * exp(I*etaV[2]);

         UV[nu][2][0] =  (s12V*s23V - c12V*s13V*c23V*exp(I*deltaV)) * exp(I*etaV[0]);
         UV[nu][2][1] = -(c12V*s23V + s12V*s13V*c23V*exp(I*deltaV)) * exp(I*etaV[1]);
         UV[nu][2][2] =  c13V*c23V * exp(I*etaV[2]);

         UV[antinu]=Conjugate(UV[nu]);
        }


// ********************************************************************************

array<MATRIX<complex<double>,NF,NF>,NF> CofactorMatrices(MATRIX<complex<double>,NF,NF> H,array<double,NF> k)
      { array<MATRIX<complex<double>,NF,NF>,NF> CC;
         
        for(int j=0;j<=NF-1;j++)
           { CC[j][e][e] = (H[mu][mu]-k[j])*(H[tau][tau]-k[j]) - norm(H[mu][tau]);
             CC[j][e][mu] = H[mu][tau]*H[tau][e]-H[mu][e]*(H[tau][tau]-k[j]);
             CC[j][e][tau] = H[tau][mu]*H[mu][e]-H[tau][e]*(H[mu][mu]-k[j]);

             CC[j][mu][e] = H[e][tau]*H[tau][mu]-H[e][mu]*(H[tau][tau]-k[j]);
             CC[j][mu][mu] = (H[e][e]-k[j])*(H[tau][tau]-k[j]) - norm(H[e][tau]);
             CC[j][mu][tau] = H[tau][e]*H[e][mu]-H[tau][mu]*(H[e][e]-k[j]);

             CC[j][tau][e] = H[e][mu]*H[mu][tau]-H[e][tau]*(H[mu][mu]-k[j]);
             CC[j][tau][mu] = H[mu][e]*H[e][tau]-H[mu][tau]*(H[e][e]-k[j]);
             CC[j][tau][tau] = (H[e][e]-k[j])*(H[mu][mu]-k[j]) - norm(H[e][mu]);
            }

        return CC;
       }

void CofactorMatrices(MATRIX<complex<double>,NF,NF> H,array<double,NF> k,array<MATRIX<complex<double>,NF,NF>,NF> &CC)
      { for(int j=0;j<=NF-1;j++)
           { CC[j][e][e] = (H[mu][mu]-k[j])*(H[tau][tau]-k[j]) - norm(H[mu][tau]);
             CC[j][e][mu] = H[mu][tau]*H[tau][e]-H[mu][e]*(H[tau][tau]-k[j]);
             CC[j][e][tau] = H[tau][mu]*H[mu][e]-H[tau][e]*(H[mu][mu]-k[j]);

             CC[j][mu][e] = H[e][tau]*H[tau][mu]-H[e][mu]*(H[tau][tau]-k[j]);
             CC[j][mu][mu] = (H[e][e]-k[j])*(H[tau][tau]-k[j]) - norm(H[e][tau]);
             CC[j][mu][tau] = H[tau][e]*H[e][mu]-H[tau][mu]*(H[e][e]-k[j]);

             CC[j][tau][e] = H[e][mu]*H[mu][tau]-H[e][tau]*(H[mu][mu]-k[j]);
             CC[j][tau][mu] = H[mu][e]*H[e][tau]-H[mu][tau]*(H[e][e]-k[j]);
             CC[j][tau][tau] = (H[e][e]-k[j])*(H[mu][mu]-k[j]) - norm(H[e][mu]);
            }
       }


