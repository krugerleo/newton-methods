#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <matheval.h>
#include "dados.h"
#include "sistema.h"

SistemaL *alocaSistemaLinear(unsigned int n){
    SistemaL *SL= (SistemaL *) malloc(sizeof(SistemaL));
    SL->dimensao = n;
    SL->vtrVariaveis = (double *)malloc((sizeof(double *)*n));
    SL->matrizHessianaEval = (void ***) malloc( sizeof(void **) * n);
    for(int i = 0; i < n; i++){
        SL->matrizHessianaEval[i] = (void **) malloc( sizeof(void*) * n);
    }   
    SL->vtrDerivadasEval = (void *)malloc((sizeof(void *)*n));
    SL->nomesVariaveis=(char **)malloc((sizeof(char **)*n*4));
    SL->matrizHessiana  = (double **) malloc( sizeof(double **) * SL->dimensao);
    SL->deltaFuncoes   = (double *) malloc( sizeof(double *) * SL->dimensao);
    SL->delta      = (double *) malloc( sizeof(double *) * SL->dimensao);
    
    for(int i = 0; i < SL->dimensao; i++){
        SL->matrizHessiana[i] = (double *) malloc( sizeof(double*) * SL->dimensao);
    }  
    return SL;
}
SistemaL *criaSistemaLinear(DadosE *DE){

    int count;
    SistemaL *sistemaLinear;
    sistemaLinear = alocaSistemaLinear(DE->Qnt_variaveis);    
    

    // First value to vector
    for(int i = 0; i < DE->Qnt_variaveis; ++i){
        sistemaLinear->vtrVariaveis[i]=DE->Ap_inicial[i];
    }
    // create evaluator
    void *f = evaluator_create(DE->Funcao);
    assert (f);
    // Get nomes variaveis with matheval
    evaluator_get_variables (f, &sistemaLinear->nomesVariaveis,&count);
    
    // Cria vetor de derivadas
    
    for(int i = 0; i < count; i++){
        sistemaLinear->vtrDerivadasEval[i] = evaluator_derivative(f, sistemaLinear->nomesVariaveis[i]);
        //evaluate_evalueter
        // printf("\nDerivada x%d: %s\n",i,evaluator_get_string(t[i]));
    }
    // Cria matriz Hess
    for(int i = 0; i < count; i++){
        for(int j = 0; j < count; j++){
            // derivada segunda
            // printf("\n %p,[%d][%d]\n",&sistemaLinear->matrizHessiana[i][j],i,j );
            sistemaLinear->matrizHessianaEval[i][j] = evaluator_derivative(sistemaLinear->vtrDerivadasEval[i], sistemaLinear->nomesVariaveis[j]);
            // printf("\n%s\n",evaluator_get_string(A[i][j]));
        }
    }


    return sistemaLinear;
}