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
            matrizAux[i][j] = evaluator_evaluate(SL->matrizHessianaEval[i][j],SL->dimensao,SL->nomesVariaveis,SL->vtrVariaveis);        
            // printf("%lf\t",matrizAux[i][j]);
        }
        // printf("\n");
    }

    
    return matrizAux;
   // double delta= //vetor da funçaõ derivadas e aplicaco a interação
}

double *montaDeltaF( SistemaL *SL){
    
    double *deltaAux = (double *)malloc((sizeof(double *)*SL->dimensao));
    for (int i = 0; i < SL->dimensao; i++){
        // printf("\nDerivada x%d: %s\n Valor x%d: %lf",(i+1),evaluator_get_string(SL->vtrDerivadasEval[i]),(i+1),SL->vtrVariaveis[i]);
        deltaAux[i] = (-1.0) * evaluator_evaluate(SL->vtrDerivadasEval[i],SL->dimensao,SL->nomesVariaveis,SL->vtrVariaveis);
        // printf("\nValor calculado: %lf\n",deltaAux[i]);
    }
    return deltaAux;
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
void newton(SistemaL *SL, DadosE *DE){
    double max;
    double normadelta;
    
    
    
    max     = calculaNorma(SL->vtrVariaveis,SL->dimensao);
    SL->matrizHessiana  = montamatriz(SL); 
    SL->deltaFuncoes    = montaDeltaF(SL);    

    printf("\n%s\n",DE->Funcao);
    printf("#Iteração\t| Newton Padrão\t| Newton Modificado\t| Newton Inexato\n");
    int x = 0;
    while (1 )
    {   
        printf("%d\t\t|",x);        
        //Gauss
        triang(SL);
        retrossubs(SL);
        printf("%lf\t|", evaluator_evaluate(SL->funcao,SL->dimensao,SL->nomesVariaveis,SL->delta) );
        //Gauss Steps
        
        
        // gaussSteps();
        // gaussSeidel();
        calculaProximoX(SL);
        x++;
        break;
    }
    
    

} 

void calculaProximoX(SistemaL *SL){
    for (int i = 0; i < SL->dimensao; i++)
    {
        SL->vtrVariaveis[i] = SL->vtrVariaveis[i] + SL->delta[i];
    }
    SL->matrizHessiana  = montamatriz(SL); 
    SL->deltaFuncoes    = montaDeltaF(SL); 
    
}

void pivot(SistemaL *SL, int i) {
    double max = fabs(SL->matrizHessiana[i][i]);
    int max_i = i;
    for (int j = i+1; j < SL->dimensao; ++j) {
            double v = fabs(SL->matrizHessiana[j][i]);
        if (v > max) {
            max = v;
            max_i = j;
        }
    }
    if (max_i != i) {
        double *tmp = SL->matrizHessiana[i];
        SL->matrizHessiana[i] = SL->matrizHessiana[max_i];
        SL->matrizHessiana[max_i] = tmp;

        double aux = SL->deltaFuncoes[i];
        SL->deltaFuncoes[i] = SL->deltaFuncoes[max_i];
        SL->deltaFuncoes[max_i] = aux;
    }
} 

void retrossubs(SistemaL *SL) {
    for (int i = SL->dimensao-1; i >=0; --i) {
        SL->delta[i] = SL->deltaFuncoes[i];
        for (int j = i+1; j < SL->dimensao; j++)
            SL->delta[i] -= SL->matrizHessiana[i][j] * SL->delta[j];
            SL->delta[i] /= SL->matrizHessiana[i][i];
        }   
}

void triang(SistemaL *SL) {
    for (int i = 0; i < SL->dimensao; ++i) {
        pivot(SL, i);
        for (int k = i+1; k < SL->dimensao; ++k) {
            double m = SL->matrizHessiana[k][i] / SL->matrizHessiana[i][i];
        if (isnan(m))
            printf("ERRO: %g\n", SL->matrizHessiana[i][i]);
        SL->matrizHessiana[k][i] = 0.0;
        for (int j = i+1; j < SL->dimensao; ++j)
            SL->matrizHessiana[k][j] -= SL->matrizHessiana[i][j] * m;
        SL->deltaFuncoes[k] -= SL->deltaFuncoes[i] * m;
        }
    }
} 
