#include <stdio.h>
#include <stdlib.h>
#include "testeentrada.h"
#include "funcoes.h"



SistemaL_Convertido *alocaSistemaLConvertido(unsigned int n){
    printf("entrou sistema convertido\n");
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
    SistemaL_Convertido *Novo_Sistema = NULL;
    Novo_Sistema = alocaSistemaLConvertido(SL->Qnt_variaveis);
    printf("deu certo Sistema convertido \n");
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
   
    unsigned n;
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
    }
    scanf("%s",SL->Funcao);
    scanf("%lf",SL->Ap_inicial);
    scanf("%Lg",SL->Tole_epsilon);
    scanf("%lf",SL->Max_interacao);
    
    //scanf("%d",SL->Qnt_variaveis);
    //scanf("%s",SL->Funcao);
    //scanf("%lf",SL->Ap_inicial);
    return SL;
}