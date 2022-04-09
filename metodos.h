#ifndef METODOS_H
#define METODOS_H

double calculaNorma(double *X,int n);

double **montamatriz(SistemaL *SL);

double *montaDeltaF(SistemaL *SL);

void gaussSeidel(SistemaL *SL);

long double calculoNormaDelta(double *delta, int n);

void newton(SistemaL *SL, DadosE *DE);

void pivot(SistemaL *SL, int i);

void retrossubs(SistemaL *SL);

void triang(SistemaL *SL);

void calculaProximoX(SistemaL *SL);

void triangLU(double **L,double **U,SistemaL *SL);

void eliminacaoGauss(SistemaL *SL);
void gpivot(double **A,double *B, int tam, int i);
void gretrossubs(double **A, double *X, double *B, int tam);
void gretrossubsInf(double **A, double *X, double *B, int tam);
void gtriang(double **A,double *B,int tam);
void resolveLY(double **A,double *X,double *B,int tam);
void resolveUX(double **A,double *X,double *B,int tam);
#endif