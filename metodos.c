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

long double calculoNormaDelta(double *delta, int n){
    long double soma,quadrado;
    soma=0;
    for(int i = 0;i<n;i++){
        quadrado = delta[i]*delta[i];
        soma = soma+quadrado;
    }
    
    return sqrt(soma);
}


void newton(SistemaL *SL, DadosE *DE){
    double max;
    long double normaDeltaI;
    long double normaDeltaF;
    SistemaL *sistemaAux;
    sistemaAux = alocaSistemaLinear(DE->Qnt_variaveis);    
    
    max= calculaNorma(SL->vtrVariaveis,SL->dimensao);
    SL->matrizHessiana  = montamatriz(SL); 
    SL->deltaFuncoes    = montaDeltaF(SL);    

    printf("\n%s\n",DE->Funcao);
    printf("#Iteração\t| Newton Padrão\t| Newton Modificado\t| Newton Inexato\n");
    int x = 0;
    normaDeltaI=15;
    normaDeltaF=calculoNormaDelta(SL->deltaFuncoes,SL->dimensao);
    sistemaAux=SL;
    printf("1 ---- NORMA DE DELTA = %LF e NORMA DE DELTAI %LF \n", normaDeltaF,normaDeltaI);
    while ( (normaDeltaF > DE->Tole_epsilon) &&  (normaDeltaI > DE->Tole_epsilon)){       
        printf("%d\t\t|",x);        
        //Gauss
        triang(sistemaAux);
        retrossubs(sistemaAux);
        
       // printf("NORMA DELTA %Lf\n",normaDeltaI);
        printf("%1.14e\t|\n", evaluator_evaluate(sistemaAux->funcao,sistemaAux->dimensao,sistemaAux->nomesVariaveis,sistemaAux->vtrVariaveis) );
        //Gauss Steps
        
        
        // gaussSteps();
        // gaussSeidel();
        
        calculaProximoX(sistemaAux);
        normaDeltaI=calculoNormaDelta(sistemaAux->delta,sistemaAux->dimensao);
        normaDeltaF=calculoNormaDelta(sistemaAux->deltaFuncoes,sistemaAux->dimensao);
        /*for(int k = 0; k< SL->dimensao;k++){
            sistemaAux->delta[k]=0.0;
        }*/
        x++;
    }
     printf("%1.14e \t\t\t|", evaluator_evaluate(sistemaAux->funcao,sistemaAux->dimensao,sistemaAux->nomesVariaveis,sistemaAux->vtrVariaveis) );
        
    sistemaAux=SL;
    normaDeltaI=15;
    normaDeltaF=calculoNormaDelta(SL->deltaFuncoes,SL->dimensao);
    x=0;
    printf("antes do while\n");
    printf("2 ---- NORMA DE DELTA = %LF e NORMA DE DELTAI %LF \n", normaDeltaF,normaDeltaI);
    while ( (normaDeltaF > DE->Tole_epsilon) &&  (normaDeltaI > DE->Tole_epsilon)){   
        printf("entrou segundo while");
        printf("%d\t\t|",x);        
        //Gauss
        triang(sistemaAux);
        retrossubs(sistemaAux);
        
        // printf("NORMA DELTA %Lf\n",normaDeltaI);
        printf("%1.14e\t\t\t|\n", evaluator_evaluate(sistemaAux->funcao,sistemaAux->dimensao,sistemaAux->nomesVariaveis,sistemaAux->vtrVariaveis) );
        //Gauss Steps
        
    
        calculaProximoX(sistemaAux);
        normaDeltaI=calculoNormaDelta(sistemaAux->delta,sistemaAux->dimensao);
        normaDeltaF=calculoNormaDelta(sistemaAux->deltaFuncoes,sistemaAux->dimensao);
        for(int k = 0; k< SL->dimensao;k++){
            SL->delta[k]=0.0;
        }
        x++;
        
    }
    
    
   

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
