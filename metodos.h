#ifndef METODOS_H
#define METODOS_H

double calculaNorma(double *X,int n);

double **montamatriz(SistemaL *SL, DadosE *DE);

void newtonNormal(SistemaL *SL,DadosE *dadosEntrada);
#endif