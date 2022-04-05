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
    SL->matrizCoeficientes = NULL; // como alocar?
    SL->termosIndependentes = (double *)malloc((sizeof(double *)*n));
    return SL;
}
SistemaL *criaSistemaLinear(DadosE *DE){
    char **nomesVariaveis;
    int count;
    SistemaL *sistemaLinear = NULL;
    sistemaLinear = alocaSistemaLinear(DE->Qnt_variaveis);

    nomesVariaveis=(char **)malloc((sizeof(char **)*DE->Qnt_variaveis*4));
    for(int i = 0; i < DE->Qnt_variaveis; ++i){
        sistemaLinear->vtrVariaveis[i]=DE->Ap_inicial[i];
    }
    
    void *f = evaluator_create(DE->Funcao);
    assert (f);
    evaluator_get_variables (f, &nomesVariaveis,&count);
    
    
    for(int i = 0; i < count; i++){
        printf ("%s ", nomesVariaveis[i]);
    }
    
    // Cria vetor de derivadas
    void **t = (void *)malloc((sizeof(void *)*count));
    for(int i = 0; i < count; i++){
        t[i] = evaluator_derivative(f, nomesVariaveis[i]);
        printf("\nDerivada x%d: %s\n",i,evaluator_get_string(t[i]));
    }
    // Cria matriz Hess
    void *(*A)[count] = malloc(sizeof(int[count][count]));
    for(int i = 0; i < count; i++){
        for(int j = 0; j < count; j++){
            A[i][j] = evaluator_derivative(t[i], nomesVariaveis[j]);
            printf("Deriva 2 i:%d j:%d == %s",i,j,evaluator_get_string(A[i][j]));
        }
        
    }
    /*
    void *derivadas;
    passar apinicial -> M 
    names=pega os nomes
    for
      derivadas[i] = evalue_derivada(names,DE->fucao)
    

    */

    return sistemaLinear;
}