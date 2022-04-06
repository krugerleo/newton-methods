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
    
    matrizAux = (double **) malloc( sizeof(double **) * SL->dimensao);
    for(int i = 0; i < SL->dimensao; i++){
        matrizAux[i] = (double *) malloc( sizeof(double*) * SL->dimensao);
    }  
  

    // Get nomes variaveis with matheval
    // evaluator_get_variables (f, &SL->nomesVariaveis,&count);
    //evaluator_evaluate(hessiana[i][j],n,vtr,apiicial,)
   

    for(int i =0;i<DE->Qnt_variaveis;i++){
        for(int j =0;j<DE->Qnt_variaveis;j++){
            //Evaluator('Função derivada dupla de F -> evaluator',
                    //  'Dimensão de F -> int',
                    //  'Vetor nomes variaveis -> (x1,x2, ..., xn)')
                    //  'Valor de uma variavel xn -> double (ap inicial);
            matrizAux[i][j]=evaluator_evaluate(SL->matrizHessiana[i][j],SL->dimensao,SL->nomesVariaveis,&SL->vtrVariaveis[j]);
        }
    }
   
    return matrizAux;
   // double delta= //vetor da funçaõ derivadas e aplicaco a interação
}

void newtonNormal(SistemaL *SL, DadosE *DE){
    double max;
    double **matrizValores;
    double *delta;
    
    matrizValores  = (double **) malloc( sizeof(double **) * SL->dimensao);
    delta   = (double *) malloc( sizeof(double *) * SL->dimensao);
    for(int i = 0; i < SL->dimensao; i++){
        matrizValores[i] = (double *) malloc( sizeof(double*) * SL->dimensao);
    }  
    max     = calculaNorma(SL->vtrVariaveis,SL->dimensao);
    matrizValores  = montamatriz(SL,DE); 
        /*for (int i=0; i<DE->Qnt_variaveis;i++) {
            for (int j=0; j<DE->Qnt_variaveis;j++) {
                printf("%lf ", matriz[i][j]);
            }
        printf("\n"); // para pular linha quando terminar a coluna
        }*/
    
      
    printf("max retornado igual = %lf\n",max);
} 