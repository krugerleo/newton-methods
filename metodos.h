#ifndef METODOS_H
#define METODOS_H

double calculaNorma(double *X,int n);

double **montamatriz(SistemaL *SL);

double *montaDeltaF(SistemaL *SL);

double calculoNormaDelta(double *delta, int n);

void newtonNormal(SistemaL *SL);

void pivot(SistemaL *SL, int i);

void retrossubs(SistemaL *SL);

void triang(SistemaL *SL);
#endif