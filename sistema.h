#ifndef SISTEMA_H
#define SISTEMA_H

typedef struct {
    int dimensao;                   // dimensão do SL
    //double tempoDerivadas;          // ?
    double *vtrVariaveis;           // vetor nxn de posições da matriz Guarda aproximação inicial
    void ***matrizHessianaEval;     // Matriz evaluator for hessiana
    void **vtrDerivadasEval;        // Vetor evaluator for Delta F
    char **nomesVariaveis;          // Nomes variaveis
    double **matrizHessiana;        // matrix hessiana com valores
    double *deltaFuncoes;           // vetor valores do delta das funções 
    double *delta;                  // vetor valores de delta
    void *funcao;                   // eval da função
    
} SistemaL;

SistemaL *alocaSistemaLinear(unsigned int n);

SistemaL *criaSistemaLinear(DadosE *DE);

//void imprimeMatriz(double **m, int tam);

void freeSistemaLinear(SistemaL *SL);

#endif
