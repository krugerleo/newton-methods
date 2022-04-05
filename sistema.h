#ifndef ENTRADA_H
#define ENTRADA_H

typedef struct {
    int Qnt_variaveis;
    char *Funcao;
    double *Ap_inicial;
    long double *Tole_epsilon;
    double *Max_interacao;
} Dados_Entrada;

typedef struct {
    int Dimensao;   // dimensão do SL
    double *VetorM;        // vetor nxn de posições da matriz
    double **Mcoeficientes;       // matriz dos coeficientes do SL (vetor de ponteiros para posições de M)
    double *Termos_Independentes;  
} SistemaL;
#endif
