#ifndef __ROSENBROCK__
#define __ROSENBROCK__

/* Função Rosenbrock de dimensão n.
 * Devolve f(X)
 */
double rosenbrock(double *X, int n);

/* Derivada parcial de primeira ordem da função Rosenbrock de dimensão n
 * em relação à variável xi, considerando X = (x0, x1, ..., xn-1).
 * Devolve df/dx_i (X)
 */
double rosenbrock_dx(int i, double *X, int n);

/* Derivada parcial de segunda ordem da função Rosenbrock de dimensão n
 * em relação às variáveis xi e xj, considerando X = (x0, x1, ..., xn-1).
 * Devolve d^2f/dx_idx_j (X)
 */
double rosenbrock_dxdy(int i, int j, double *X, int n);

#endif
