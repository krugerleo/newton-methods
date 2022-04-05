#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <matheval.h>
#include <assert.h>
#include "sistema.h"
#include "funcoes.h"
#define DEBUG 1
#define debug_print(args ...) if (DEBUG) printf(stderr, args)

#define BUFFER_SIZE 256
#define ncaracteres  1000



SistemaL *alocaSistemaLConvertido(unsigned int n){

    SistemaL *SL= (SistemaL *) malloc(sizeof(SistemaL));
    SL->Dimensao = n;
    SL->VetorM = (double *)malloc((sizeof(double *)*n));
    SL->Mcoeficientes = (double **)malloc((sizeof(double **)*(n*n)));
    SL->Termos_Independentes = (double *)malloc((sizeof(double *)*n));
    return SL;
}
SistemaL *converteMatriz(Dados_Entrada *DE){
    SistemaL *Novo_Sistema = NULL;

    Novo_Sistema = alocaSistemaLConvertido(DE->Qnt_variaveis);


    return Novo_Sistema;
}
Dados_Entrada *alocaDados(unsigned int n){

    Dados_Entrada *DE = (Dados_Entrada *) malloc(sizeof(Dados_Entrada));
    DE->Qnt_variaveis = n;
    DE->Funcao=(char *)malloc(sizeof(char *)*ncaracteres);
    DE->Ap_inicial=(double *)malloc((sizeof(double *)*n));
    DE->Tole_epsilon=(long double *)malloc(sizeof(long double *));
    DE->Max_interacao=(double *)malloc(sizeof(double *));
    return DE;
}
Dados_Entrada *lerDados(){
   
    unsigned int n;
    Dados_Entrada *DE = NULL;
    
    if (scanf("%d",&n) != EOF) {  
        DE = alocaDados(n);

        scanf("%s",DE->Funcao);
        for(int i = 0; i <= n; ++i){
              scanf("%lf",&DE->Ap_inicial[i]);
        };
        scanf("%Lg",DE->Tole_epsilon);
        scanf("%lf",DE->Max_interacao);
    }

    return DE;
}
