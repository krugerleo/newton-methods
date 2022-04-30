#ifndef __ROSENBROCK__
#define __ROSENBROCK__

#include "Rosenbrock.h"
#include <stdio.h>
/* Função Rosenbrock de dimensão n.
 * Devolve f(X)
 */
double rosenbrock(double *X, int n) {
  double sum = 0;
  for (int i = 0; i < n-1; ++i) {
    double p1 = X[i+1]-X[i]*X[i];
    double p2 = 1-X[i];
    sum += 100*p1*p1 + p2*p2;
  }
  return sum;
}

/* Derivada parcial de primeira ordem da função Rosenbrock de dimensão n
 * em relação à variável xi, considerando X = (x0, x1, ..., xn-1).
 * Devolve df/dx_i (X)
 */
double rosenbrock_dx(int i, double *X, int n) {
    double dxi;
    if (i == 0)
        dxi = 2*(200*X[0]*X[0]*X[0] - 200*X[0]*X[1] + X[0] - 1);
    else if (i == n-1)
        dxi = 200*(X[n-1]-X[n-2]*X[n-2]);
    else
        dxi = -200*X[i-1]*X[i-1] + 400*X[i]*X[i]*X[i] + X[i]*(202 - 400*X[i+1]) - 2;
    return dxi;
}

/* Derivada parcial de segunda ordem da função Rosenbrock de dimensão n
 * em relação às variáveis xi e xj, considerando X = (x0, x1, ..., xn-1).
 * Devolve d^2f/dx_idx_j (X)
 */
double rosenbrock_dxdy(int i, int j, double *X, int n) {
    double dxidxj;
    if (i == 0) {
        if (j == 0)
            dxidxj = 1200*X[0]*X[0] - 400*X[1] + 2;
        else if (j == 1)
            dxidxj = -400*X[0];
        else
            dxidxj = 0;
    }
    else if (i == n-1) {
        if (j == n-2)
            dxidxj = -400*X[n-2];
        else if (j == n-1)
            dxidxj = 200;
        else
            dxidxj = 0;        
    }
    else {
        if (j == i-1)
            dxidxj = -400*X[i-1];
        else if (j == i)
            dxidxj = 1200*X[i]*X[i] - 400*X[i+1] + 202;
        else if (j == i+1)
            dxidxj = -400*X[i];
        else
            dxidxj = 0;
    }
    return dxidxj;
}

#endif
