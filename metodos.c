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
   
    printf("Antes do for\n");
    for(int i =0;i<DE->Qnt_variaveis;i++){
        for(int j =0;j<DE->Qnt_variaveis;j++){
            //Evaluator('Função derivada dupla de F -> evaluator',
                    //  'Dimensão de F -> int',
                    //  'Vetor nomes variaveis -> (x1,x2, ..., xn)')
                    //  'Valor de uma variavel xn -> double (ap inicial);
            matrizAux[i][j]=evaluator_evaluate(SL->matrizHessiana[i][j],SL->dimensao,SL->nomesVariaveis,&SL->vtrVariaveis[j]);
            matrizAux[i][j]=matrizAux[i][j]*(SL->vtrVariaveis[j]);
        }
    }
    
    return matrizAux;
   // double delta= //vetor da funçaõ derivadas e aplicaco a interação
}

double *montaDeltaF(double **matrizValores, SistemaL *SL, DadosE *DE){
    printf("entrou deltaF\n");
    double *deltaAux = (double *)malloc((sizeof(double *)*SL->dimensao));
    for (int i = 0; i < SL->dimensao; i++){
        deltaAux[i]=evaluator_evaluate(SL->vtrDerivadas[i],SL->dimensao,SL->nomesVariaveis,&SL->vtrVariaveis[i]);
        
        printf("delta =%lf \n",deltaAux[i]);
    }
    
}

double calculoNormaDelta(double *delta, int n){
    double soma,quadrado;
    soma=0;
    for(int i = 0;i<n;i++){
        quadrado=pow(delta[i],2);
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
    
    printf("--------------------MATRIZ HESSIANA-------------------------\n");
    for (int i=0; i<DE->Qnt_variaveis;i++) {
        for (int j=0; j<DE->Qnt_variaveis;j++) {
            printf("%s ", evaluator_get_string(SL->matrizHessiana[i][j]));
        }
    printf("\n"); // para pular linha quando terminar a coluna
    }
    
    for(int j =0;j<DE->Qnt_variaveis;j++){    
        printf("Vetor de DErivadas = %s \n Dimensão=%d \n Nomes Variaveis=%s \n Vtr de variaveis=%lf\n",evaluator_get_string(SL->vtrDerivadas[j]),SL->dimensao,SL->nomesVariaveis[j],SL->vtrVariaveis[j]);
    }

    
    max     = calculaNorma(SL->vtrVariaveis,SL->dimensao);
    matrizValores  = montamatriz(SL,DE); 
    delta=montaDeltaF(matrizValores,SL,DE);
    /*for (int i=0; i<DE->Qnt_variaveis;i++) {
        for (int j=0; j<DE->Qnt_variaveis;j++) {
            printf("%lf ", matrizValores[i][j]);
        }
    printf("\n"); // para pular linha quando terminar a coluna
    }*/
    normadelta=calculaNormaDelta(delta,SL->dimensao);
      
    printf("max retornado igual = %lf\n",max);
} 