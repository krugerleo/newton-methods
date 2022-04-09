#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <matheval.h>
#include "utils.h"
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

long double calculoNormaDelta(double *delta, int n){
    long double soma,quadrado;
    soma=0;
    for(int i = 0;i<n;i++){
        quadrado = delta[i]*delta[i];
        soma = soma+quadrado;
    }
    
    return sqrt(soma);
}

void gaussSeidel(SistemaL *SL){
    int contador = 0;
    int n=SL->dimensao;
    double oldDelta[n];
    double parada[n];
   

    for (int i = 0; i < n; i++){
        oldDelta[i]=0;
    }
    parada[0] = 10;
    while (contador<50 && (calculoNormaDelta(parada,n)>pow(10,-6))) {
        for(int i =0;i<n;i++){
            SL->delta[i]=SL->deltaFuncoes[i];
            for(int j = 0;j<n;j++){
                if(j!=i){
                    SL->delta[i]-=SL->matrizHessiana[i][j]*SL->delta[j];
                }
            }
            SL->delta[i] = SL->delta[i] / SL->matrizHessiana[i][i];
        }
        for(int i=0;i<n;i++){
            parada[i] = SL->delta[i]-oldDelta[i];
            oldDelta[i]=SL->delta[i];
        }
        contador++;
    }
    
}
void newton(SistemaL *SL, DadosE *DE){
    double max;
    long double normaDeltaI;
    long double normaDeltaF;

    double sistemaTempo;
    double gaussTempo;
    double gstepsTempo;
    double gseidelTempo;

    double **matrizL;
    double **matrizU;
    matrizL = (double **) malloc( sizeof(double **) * SL->dimensao);
    for(int i = 0; i < SL->dimensao ; i++){
        matrizL[i] = (double *) malloc( sizeof(double*) * SL->dimensao);
    }  
    matrizU = (double **) malloc( sizeof(double **) * SL->dimensao);
    for(int i = 0; i < SL->dimensao; i++){
        matrizU[i] = (double *) malloc( sizeof(double*) * SL->dimensao);
    }  
    
    //double *respostaGauss;
    //respostaGauss = (double **) malloc( sizeof(double **) * SL->dimensao);
    SistemaL *sistemaAux;
    SistemaL *sistemaSteps;
    sistemaTempo=timestamp();
    sistemaAux = alocaSistemaLinear(DE->Qnt_variaveis);    
    
    //fazer um vetor que guarda respostas
    max= calculaNorma(SL->vtrVariaveis,SL->dimensao);
    SL->matrizHessiana  = montamatriz(SL); 
    SL->deltaFuncoes    = montaDeltaF(SL);    
    sistemaTempo=timestamp()-sistemaTempo;
    printf("\n%s\n",DE->Funcao);
    printf("#Iteração\t| Newton Padrão\t\t| Newton Modificado\t| Newton Inexato\n");
    int x = 0;
    normaDeltaI=15;
    normaDeltaF=calculoNormaDelta(SL->deltaFuncoes,SL->dimensao);
    sistemaAux=SL;
    sistemaSteps = alocaSistemaLinear(DE->Qnt_variaveis);    
    sistemaSteps=SL;
    
    while ( (normaDeltaF > DE->Tole_epsilon) ||  (normaDeltaI > DE->Tole_epsilon)){       
        printf("%d\t\t|",x);        
        //Gauss
        gaussTempo=timestamp();
        triang(sistemaAux);
        retrossubs(sistemaAux);
        gaussTempo=timestamp() - gaussTempo;
        
        printf("%1.14e\t|", evaluator_evaluate(sistemaAux->funcao,sistemaAux->dimensao,sistemaAux->nomesVariaveis,sistemaAux->vtrVariaveis) );
        
        //Gauss Steps
        gstepsTempo=timestamp();
        triangLU(matrizL,matrizU,sistemaAux);   
        // resolveLY();
        // resolveUX();
        printf("%1.14e\t|", evaluator_evaluate(sistemaAux->funcao,sistemaAux->dimensao,sistemaAux->nomesVariaveis,sistemaAux->vtrVariaveis) );
        gstepsTempo=timestamp() - gstepsTempo;
        
        // gauss seidel
        gseidelTempo=timestamp();
        gaussSeidel(sistemaAux);
        gseidelTempo = timestamp() - gseidelTempo;
        printf("%1.14e\t\n", evaluator_evaluate(sistemaAux->funcao,sistemaAux->dimensao,sistemaAux->nomesVariaveis,sistemaAux->vtrVariaveis) );
        
        calculaProximoX(sistemaAux);
        normaDeltaI=calculoNormaDelta(sistemaAux->delta,sistemaAux->dimensao);
        normaDeltaF=calculoNormaDelta(sistemaAux->deltaFuncoes,sistemaAux->dimensao);
        
        x++;
    }
    printf("Tempo total \t| %1.14e\t| %1.14e\t| %1.14e  \n", gaussTempo, gstepsTempo, gseidelTempo);
    //Usa a mesma variável pois é calculado uma vez no sistema.c
    printf("Tempo derivadas | %1.14e\t| %1.14e\t| %1.14e \n", SL->tempoDerivadas, SL->tempoDerivadas, SL->tempoDerivadas);
    //Usa o mesmo valor pois o sistema é montado antes dos calculos
    printf("Tempo SL \t| %1.14e\t| %1.14e\t| %1.14e \n", sistemaTempo, sistemaTempo, sistemaTempo);    
   

    x=0;

} 

void calculaProximoX(SistemaL *SL){
    for (int i = 0; i < SL->dimensao; i++) {   
        // X(I+1) = X(I) + DELTA(I)
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

void triangLU(double **L,double **U,SistemaL *SL) {
    for (int i = 0; i < SL->dimensao;   i++) {
        for (int k = i+1; k < SL->dimensao; ++k) {
                double m = SL->matrizHessiana[k][i] / SL->matrizHessiana[i][i];
            if (isnan(m))
                printf("ERRO: %g\n", SL->matrizHessiana[i][i]);
            SL->matrizHessiana[k][i] = 0.0;
            U[k][i] = 0.0;
            L[k][i] = m ;
            for (int j = i+1; j < SL->dimensao; ++j){
                SL->matrizHessiana[k][j] -= SL->matrizHessiana[i][j] * m;
                U[k][j] = SL->matrizHessiana[k][j];
            }        
        }
        U[i][i] = SL->matrizHessiana[i][i];
        L[i][i] = 1.0;
    }

} 
