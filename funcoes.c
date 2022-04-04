#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <matheval.h>
#include <assert.h>
#include "main.h"
#include "funcoes.h"


#define BUFFER_SIZE 256



SistemaL_Convertido *alocaSistemaLConvertido(unsigned int n){

    SistemaL_Convertido *SL= (SistemaL_Convertido *) malloc(sizeof(SistemaL_Convertido));
    SL->Dimensao = n;
    SL->VetorM = (double *)malloc((sizeof(double *)*n));
    SL->Mcoeficientes = (double **)malloc((sizeof(double **)*(n*n)));
    SL->Termos_Independentes = (double *)malloc((sizeof(double *)*n));
    return SL;
    /*unsigned int n;   
    double *M;        
    double **A;       
    double *b;*/  
}
SistemaL_Convertido *converteMatriz(Sistema_Linear *SL){
    printf("entrou sistema\n");
    char **variaveis;
    int totalvariaveis,i,k,tam,lin,col,n;
    void *funcao;
    char buffer[BUFFER_SIZE];
    SistemaL_Convertido *Novo_Sistema = NULL;
   
    n=SL->Qnt_variaveis;
    Novo_Sistema = alocaSistemaLConvertido(SL->Qnt_variaveis);

    printf("antes de imprimir\n");
    strcpy(buffer,SL->Funcao);
    tam=strlen(buffer);
    buffer[tam - 1] = '\0';
    funcao = evaluator_create(buffer);
    
    printf("%s\n",buffer);
    assert(funcao);
    evaluator_get_variables(funcao, &variaveis, &totalvariaveis);
    for (i = 0; i < totalvariaveis; i++){//percorre o vetor de variaveis
        for(k=0;k<tam;k++){
            if(buffer[k]==variaveis[i])&&buffer[k-1]=='*'{
                valor=buffer[i-2];
            }else if(buffer[k]==variaveis[i]){
                valor=1;
            }
            for(col=0;col<n;col++){
                for(lin=0;lin<n;lin++){

                }
            }
        }
    }
        //printf ("%s ", variaveis[i]);
    //printf ("\n");
    /**/


 
    return Novo_Sistema;
}
Sistema_Linear *alocaSistemaLinear(unsigned int n){
    //printf("entra aloca\n");
    Sistema_Linear *SL = (Sistema_Linear *) malloc(sizeof(Sistema_Linear));
    SL->Qnt_variaveis = n;
    SL->Funcao=(char *)malloc(sizeof(char *)*n);
    SL->Ap_inicial=(double *)malloc((sizeof(double *)*n));
    SL->Tole_epsilon=(long double *)malloc((sizeof(long double *)*n));
    SL->Max_interacao=(double *)malloc((sizeof(double *)*n));
   /* double *Ap_inicial;
    double *Tole_epsilon;
    double *Max_interacao;
    //printf("%d",SL->Qnt_variaveis);
*/
    return SL;
}
Sistema_Linear *lerSistema(){
   
    unsigned int n;
   // Sistema_Linear *SL = (Sistema_Linear *) malloc(sizeof(Sistema_Linear));
    Sistema_Linear *SL = NULL;
    
    if (scanf("%d",&n) != EOF) {  
        SL = alocaSistemaLinear(n);
      /* if (!SL) return NULL;
        
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                scanf("%lf", &(SL->A[i][j]));
        
        for(int i = 0; i < n; ++i)
            scanf("%lf", &(SL->b[i]));

        */
        scanf("%s",SL->Funcao);
        scanf("%lf",SL->Ap_inicial);
        scanf("%Lg",SL->Tole_epsilon);
        scanf("%lf",SL->Max_interacao);
    }
  /*  printf("%d\n",SL->Qnt_variaveis);
    printf("%s\n",SL->Funcao);
    printf("%lf\n",*SL->Ap_inicial);
    printf("%Lg\n",*SL->Tole_epsilon);
    printf("%lf\n",*SL->Max_interacao);*/
    return SL;
}