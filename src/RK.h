
#include "SNOSHEWS.h"

#ifndef RK_H
#define RK_H

MATRIX<std::complex<double>,NF,NF> B(std::array<double,NY> y);

// ********************** The Differential Equations ***********************

void K(double lambda,double dlambda,std::vector<std::vector<std::array<double,NY> > > &Y,std::vector<std::vector<std::array<double,NY> > > &K);

#endif


