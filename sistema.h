#ifndef SISTEMA_H
#define SISTEMA_H

typedef struct {
    int Dimensao;   // dimensão do SL
    double *VetorM;        // vetor nxn de posições da matriz
    double **Mcoeficientes;       // matriz dos coeficientes do SL (vetor de ponteiros para posições de M)
    double *Termos_Independentes;
} SistemaL;

SistemaL *alocaSistemaLinear(unsigned int n);

SistemaL *criaSistemaLinear(DadosE *DE);

#endif
