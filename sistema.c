#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <matheval.h>
#include "dados.h"
#include "sistema.h"

SistemaL *alocaSistemaLinear(unsigned int n){
    printf("entra alocação");
    SistemaL *SL= (SistemaL *) malloc(sizeof(SistemaL));
    SL->Dimensao = n;
    SL->VetorM = (double *)malloc((sizeof(double *)*n));
    SL->Mcoeficientes = (double **)malloc((sizeof(double **)*(n*n)));
    SL->Termos_Independentes = (double *)malloc((sizeof(double *)*n));
    printf("finaliza alocação");
    return SL;
}
SistemaL *criaSistemaLinear(DadosE *DE){
    int qntVariaveis;
    char **vtrVariaveis;
    SistemaL *sistemaLinear = NULL;

    sistemaLinear = alocaSistemaLinear(DE->Qnt_variaveis);
    
    void **derivadas,*f;

    vtrVariaveis=(char **)malloc((sizeof(char **)*DE->Qnt_variaveis*4));
    printf("linha 35");
    for(int i=0;i<DE->Qnt_variaveis;i++){
        sistemaLinear->VetorM[i]=DE->Ap_inicial[i];
    }
    printf("linha 35");
    f= evaluator_create(DE->Funcao);
    assert (f);
    evaluator_get_variables (f, &vtrVariaveis,&qntVariaveis);
    printf("linha 35");
    for(int i=0;i<DE->Qnt_variaveis;i++){
       printf("entrou");
        derivadas[i]=evaluator_derivative(f,vtrVariaveis[i]);
        printf("%s", evaluator_get_string(derivadas[i]));
    }

    /*printf("variaveis \n");
    printf ("  ");
       for (int i = 0; i < DE->Qnt_variaveis; i++)
         printf ("%s ", vtrVariaveis[i]);
    printf ("\n");*/
    
    // TO DO CRIAR SISTEMA COM VALOROEES

    /*
    void *derivadas;
    passar apinicial -> M 
    names=pega os nomes
    for
      derivadas[i] = evalue_derivada(names,DE->fucao)
    

    */

    return sistemaLinear;
}