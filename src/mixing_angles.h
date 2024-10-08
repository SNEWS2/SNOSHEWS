
#include "SNOSHEWS.h"

#ifndef mixing_angles_H
#define mixing_angles_H

// ****************************************************************************************

MATRIX<std::complex<double>,NF,NF> MixingMatrix(MATRIX<std::complex<double>,NF,NF> Hf,std::array<double,NF> k,std::array<double,NF> dk);
void Evaluate_UV(void);

std::array<MATRIX<std::complex<double>,NF,NF>,NF> CofactorMatrices(MATRIX<std::complex<double>,NF,NF> H,std::array<double,NF> k);
void CofactorMatrices(MATRIX<std::complex<double>,NF,NF> H,std::array<double,NF> k,std::array<MATRIX<std::complex<double>,NF,NF>,NF> &CC);

template<flavour a,flavour b> std::complex<double> C(MATRIX<std::complex<double>,NF,NF> H,double k);
template<> std::complex<double> C<e,e>(MATRIX<std::complex<double>,NF,NF> H,double k);
template<> std::complex<double> C<e,mu>(MATRIX<std::complex<double>,NF,NF> H,double k);
template<> std::complex<double> C<e,tau>(MATRIX<std::complex<double>,NF,NF> H,double k);
template<> std::complex<double> C<mu,e>(MATRIX<std::complex<double>,NF,NF> H,double k);
template<> std::complex<double> C<mu,mu>(MATRIX<std::complex<double>,NF,NF> H,double k);
template<> std::complex<double> C<mu,tau>(MATRIX<std::complex<double>,NF,NF> H,double k);
template<> std::complex<double> C<tau,e>(MATRIX<std::complex<double>,NF,NF> H,double k);
template<> std::complex<double> C<tau,mu>(MATRIX<std::complex<double>,NF,NF> H,double k);
template<> std::complex<double> C<tau,tau>(MATRIX<std::complex<double>,NF,NF> H,double k);

// *************************************************************************************

template<> inline std::complex<double> C<e,e>(MATRIX<std::complex<double>,NF,NF> H,double k)
           { return (H[mu][mu]-k)*(H[tau][tau]-k)-std::norm(H[mu][tau]);}

template<> inline std::complex<double> C<e,mu>(MATRIX<std::complex<double>,NF,NF> H,double k)
           { return H[mu][tau]*H[tau][e]-H[mu][e]*(H[tau][tau]-k);}

template<> inline std::complex<double> C<e,tau>(MATRIX<std::complex<double>,NF,NF> H,double k)
           { return H[tau][mu]*H[mu][e]-H[tau][e]*(H[mu][mu]-k);}

template<> inline std::complex<double> C<mu,e>(MATRIX<std::complex<double>,NF,NF> H,double k)
           { return H[e][tau]*H[tau][mu]-H[e][mu]*(H[tau][tau]-k);}

template<> inline std::complex<double> C<mu,mu>(MATRIX<std::complex<double>,NF,NF> H,double k)
           { return (H[e][e]-k)*(H[tau][tau]-k)-std::norm(H[e][tau]);}

template<> inline std::complex<double> C<mu,tau>(MATRIX<std::complex<double>,NF,NF> H,double k)
           { return H[tau][e]*H[e][mu]-H[tau][mu]*(H[e][e]-k);}

template<> inline std::complex<double> C<tau,e>(MATRIX<std::complex<double>,NF,NF> H,double k)
           { return H[e][mu]*H[mu][tau]-H[e][tau]*(H[mu][mu]-k);}

template<> inline std::complex<double> C<tau,mu>(MATRIX<std::complex<double>,NF,NF> H,double k)
           { return H[mu][e]*H[e][tau]-H[mu][tau]*(H[e][e]-k);}

template<> inline std::complex<double> C<tau,tau>(MATRIX<std::complex<double>,NF,NF> H,double k)
           { return (H[e][e]-k)*(H[mu][mu]-k)-std::norm(H[e][mu]);}

#endif
