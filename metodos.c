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
double **montamatriz(SistemaL *SL){

    double **matrizAux;
    
    matrizAux = (double **) malloc( sizeof(double **) * SL->dimensao);
    for(int i = 0; i < SL->dimensao; i++){
        matrizAux[i] = (double *) malloc( sizeof(double*) * SL->dimensao);
    }  
    
    for(int i =0;i<SL->dimensao;i++){
        for(int j =0;j<SL->dimensao;j++){
            //Evaluator('Função derivada dupla de F -> evaluator',
                    //  'Dimensão de F -> int',
                    //  'Vetor nomes variaveis -> (x1,x2, ..., xn)')
                    //  'Valor de uma variavel xn -> double (ap inicial);
            matrizAux[i][j]=evaluator_evaluate(SL->matrizHessiana[i][j],SL->dimensao,SL->nomesVariaveis,SL->vtrVariaveis);        
            printf("%lf\t",matrizAux[i][j]);
        }
        printf("\n");
    }
    
    return matrizAux;
   // double delta= //vetor da funçaõ derivadas e aplicaco a interação
}

double *montaDeltaF(double **matrizValores, SistemaL *SL){
    
    double *deltaAux = (double *)malloc((sizeof(double *)*SL->dimensao));
    for (int i = 0; i < SL->dimensao; i++){
        printf("\nDerivada x%d: %s\n Valor x%d: %lf",(i+1),evaluator_get_string(SL->vtrDerivadas[i]),(i+1),SL->vtrVariaveis[i]);
        deltaAux[i]=evaluator_evaluate(SL->vtrDerivadas[i],SL->dimensao,SL->nomesVariaveis,SL->vtrVariaveis);
        printf("\nValor calculado: %lf\n",deltaAux[i]);
    }
    
}

double calculoNormaDelta(double *delta, int n){
    double soma,quadrado;
    soma=0;
    for(int i = 0;i<n;i++){
        quadrado = delta[i]*delta[i];
        soma = soma+quadrado;
    }
    
    return sqrt(soma);
}
void newtonNormal(SistemaL *SL, DadosE *DE){
    double max;
    double **matrizValores;
    double *delta;
    double normadelta;
    
    matrizValores  = (double **) malloc( sizeof(double **) * SL->dimensao);
    delta   = (double *) malloc( sizeof(double *) * SL->dimensao);
    for(int i = 0; i < SL->dimensao; i++){
        matrizValores[i] = (double *) malloc( sizeof(double*) * SL->dimensao);
    }  
    

    
    max     = calculaNorma(SL->vtrVariaveis,SL->dimensao);
    matrizValores  = montamatriz(SL); 
    delta=montaDeltaF(matrizValores,SL);    
      

} 