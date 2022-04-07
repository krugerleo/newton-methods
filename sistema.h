#ifndef SISTEMA_H
#define SISTEMA_H

typedef struct {
    int dimensao;                   // dimensão do SL
    double *vtrVariaveis;           // vetor nxn de posições da matriz
    void ***matrizHessianaEval;     // Matriz evaluator for hessiana
    void **vtrDerivadasEval;        // Vetir evaluator for Delta F
    char **nomesVariaveis;          // Nomes variaveis
    double **matrizHessiana;
    double *deltaFuncoes;
    double *delta;
    void *funcao;
    
} SistemaL;

SistemaL *alocaSistemaLinear(unsigned int n);

SistemaL *criaSistemaLinear(DadosE *DE);

#endif
