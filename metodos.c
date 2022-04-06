#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <matheval.h>
#include "dados.h"
#include "sistema.h"
#include "metodos.h"

double calculaNorma(double *X,int n){
    double max=fabs(X[0]);
    for(int i = 0; i < n;++i){
        double a = fabs(X[i]);
        if(max < a )
            max= a;
    }
    return max;
};
double **montamatriz(SistemaL *SL, DadosE *DE){

    double **matrizAux;
    int count;
    int n = DE->Qnt_variaveis;
    char **nomesVariaveis=(char **)malloc((sizeof(char **)*DE->Qnt_variaveis*4));
    void *f = evaluator_create(DE->Funcao);
    assert (f);

    matrizAux = (double **) malloc( sizeof(double **) * n);
    for(int i = 0; i < n; i++){
        matrizAux[i] = (double *) malloc( sizeof(double*) * n);
    }  
  

    // Get nomes variaveis with matheval
    evaluator_get_variables (f, &nomesVariaveis,&count);
    //evaluator_evaluate(hessiana[i][j],n,vtr,apiicial,)
   

    for(int i =0;i<DE->Qnt_variaveis;i++){
        for(int j =0;j<DE->Qnt_variaveis;j++){
            matrizAux[i][j]=evaluator_evaluate(f,count,nomesVariaveis,&DE->Ap_inicial[j]);
        }
    }
   
    return matrizAux;
   // double delta= //vetor da funçaõ derivadas e aplicaco a interação
}

void newtonNormal(SistemaL *SL, DadosE *DE){
    double max;
    double **matriz;
    double *delta;
    int n = DE->Qnt_variaveis;
    matriz = (double **) malloc( sizeof(double **) * n);
    delta=(double *) malloc( sizeof(double *) * n);
    for(int i = 0; i < n; i++){
        matriz[i] = (double *) malloc( sizeof(double*) * n);
    }  
    max=calculaNorma(DE->Ap_inicial,DE->Qnt_variaveis);
    matriz=montamatriz(SL,DE); 
    /*for (int i=0; i<DE->Qnt_variaveis;i++) {
        for (int j=0; j<DE->Qnt_variaveis;j++) {
            printf("%lf ", matriz[i][j]);
        }
    printf("\n"); // para pular linha quando terminar a coluna
    }*/
   
      
    printf("max retornado igual = %lf\n",max);
} 