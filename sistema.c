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
    printf("%ld",(void***)(sizeof(void *)*n*n));
    SL->matrizCoeficientes = (double **) malloc(sizeof(double *)*n);// NÃO ESTA FUNCIONANDO
    for(int i=0; i<n;i++){
        SL->matrizCoeficientes[i]=(double *) malloc(sizeof(double)*n);
    }   
    SL->termosIndependentes = (double *)malloc((sizeof(double *)*n));
    return SL;
}
SistemaL *criaSistemaLinear(DadosE *DE){

    char **nomesVariaveis;
    int count;
    SistemaL *sistemaLinear;
    sistemaLinear = alocaSistemaLinear(DE->Qnt_variaveis);    
    nomesVariaveis=(char **)malloc((sizeof(char **)*DE->Qnt_variaveis*4));

    // First value to vector
    for(int i = 0; i < DE->Qnt_variaveis; ++i){
        sistemaLinear->vtrVariaveis[i]=DE->Ap_inicial[i];
    }
    // create evaluator
    void *f = evaluator_create(DE->Funcao);
    assert (f);
    // Get nomes variaveis with matheval
    evaluator_get_variables (f, &nomesVariaveis,&count);
    
    
    for(int i = 0; i < count; i++){
        printf ("%s ", nomesVariaveis[i]);
    }
    
    // Cria vetor de derivadas
    void **t = (void *)malloc((sizeof(void *)*count));
    for(int i = 0; i < count; i++){
        t[i] = evaluator_derivative(f, nomesVariaveis[i]);
        //evaluate_evalueter
        printf("\nDerivada x%d: %s\n",i,evaluator_get_string(t[i]));
    }
    // Cria matriz Hess
    // void *(*A)[count] = malloc(sizeof(int[count][count]));
    printf("antes do for \n");
    
    for(int i = 0; i < count; i++){
        for(int j = 0; j < count; j++){
            // ###### PRINT DEBUG, IMPRIME ENDEREÇOS MAS ESTÁ ESTRANHO
            printf("lalala\n %p,[%d][%d]\n",&sistemaLinear->matrizCoeficientes[i][j],i,j );
            // ###### SEG FAULT QUANDO TENTA INSERIR O VALOR
            //scanf("%lf", &(sistemaLinear->matrizCoeficientes[i][j]));
            sistemaLinear->matrizCoeficientes[i][j]=0.0;
            // derivada segunda
            // sistemaLinear->matrizCoeficientes[i][j] = evaluator_derivative(t[i], nomesVariaveis[j]);
            // printf("\n%s\n",evaluator_get_string(A[i][j]));
        }
        
    }

    return sistemaLinear;
}