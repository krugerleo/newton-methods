#ifndef SISTEMA_H
#define SISTEMA_H

typedef struct {
    int dimensao;   // dimensão do SL
    double *vtrVariaveis;        // vetor nxn de posições da matriz
    void ***matrizHessiana;       // matriz dos coeficientes do SL (vetor de ponteiros para posições de M)
    double *termosIndependentes;
} SistemaL;

SistemaL *alocaSistemaLinear(unsigned int n);

SistemaL *criaSistemaLinear(DadosE *DE);

#endif
