#ifndef METODOS_H
#define METODOS_H

double calculaNorma(double *X,int n);

double **montamatriz(SistemaL *SL);

double *montaDeltaF(double **matrizValores, SistemaL *SL);

double calculoNormaDelta(double *delta, int n);

void newtonNormal(SistemaL *SL,DadosE *dadosEntrada);
#endif