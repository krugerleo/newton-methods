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
    long double gaussNormaDeltaI;
    long double gaussNormaDeltaF;

    long double stepsNormaDeltaI;
    long double stepsNormaDeltaF;

    long double seidelNormaDeltaI;
    long double seidelNormaDeltaF;
  

    double sistemaTempo;
    double gaussTempo;
    double gstepsTempo;
    double gseidelTempo;

    // Variaveis LU
    double **matrizL;
    double **matrizU;
    double *y;
    // Aloca LU
    y = (double *) malloc( sizeof(double *) * SL->dimensao);
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
    SistemaL *sitemaGauss;
    SistemaL *sitemaSteps;
    SistemaL *sistemaSeidel;
    
    sistemaTempo=timestamp();
    // Aloca sistemas ()
    sitemaGauss = alocaSistemaLinear(DE->Qnt_variaveis);
    sitemaSteps = alocaSistemaLinear(DE->Qnt_variaveis);
    sistemaSeidel = alocaSistemaLinear(DE->Qnt_variaveis);    
    
    //fazer um vetor que guarda respostas
    max = calculaNorma(SL->vtrVariaveis,SL->dimensao);
    SL->matrizHessiana  = montamatriz(SL); 
    SL->deltaFuncoes    = montaDeltaF(SL);    
    sistemaTempo=timestamp()-sistemaTempo;
    printf("\n%s\n",DE->Funcao);
    printf("#Iteração\t| Newton Padrão\t\t| Newton Modificado\t| Newton Inexato\n");
    int x = 0;

    gaussNormaDeltaI=15;
    gaussNormaDeltaF=calculaNorma(SL->deltaFuncoes,SL->dimensao);
    printf("primeiro inteção gauss %Lf \n",gaussNormaDeltaF);
    
    stepsNormaDeltaI=15;
    stepsNormaDeltaF=calculaNorma(SL->deltaFuncoes,SL->dimensao);
    printf("primeiro inteção steps %Lf \n",stepsNormaDeltaF);
    seidelNormaDeltaI=15;
    seidelNormaDeltaF=calculaNorma(SL->deltaFuncoes,SL->dimensao);
    printf("primeiro inteção seidel %Lf \n",seidelNormaDeltaF);
    // Copia ?
    sitemaGauss=SL;
    sistemaSeidel=SL;
    sitemaSteps=SL;
    int it = 3;
    int teste =verificaParada(gaussNormaDeltaI,gaussNormaDeltaF,stepsNormaDeltaI,stepsNormaDeltaI,seidelNormaDeltaF,seidelNormaDeltaF,DE->Tole_epsilon);
    printf("retorno da funçaõ parada = %d \n ",teste);
    while ( teste!=0){       
        printf("primeiro inteção gauss %Lf \n",gaussNormaDeltaF);
        printf("%d\t\t|",x);        
        //Gauss
        gaussTempo=timestamp();
        eliminacaoGauss(sitemaGauss);
        gaussTempo=timestamp() - gaussTempo;
        
        //LEO PQ ELE TA IMPRIMINDO O LALAL NA PRIMEIRA INTERAÇÃO? ACHO QUE É A MESMA COISA QUE TA BUGANDO O LAÇO 
       //if((gaussNormaDeltaF > DE->Tole_epsilon) || (gaussNormaDeltaI > DE->Tole_epsilon)){
          printf("%1.14e\t|", evaluator_evaluate(sitemaGauss->funcao,sitemaGauss->dimensao,sitemaGauss->nomesVariaveis,sitemaGauss->vtrVariaveis) );
        /*}else{
          printf("\n NormaDeltaF: %Lf gaussNormaDeltaI: %Lf DE->Tole_epsilon: %Lf \n",gaussNormaDeltaF,gaussNormaDeltaI,DE->Tole_epsilon);
        //}*/
        
        //Gauss Steps
        gstepsTempo=timestamp();
        if( x % it == 0 ){
            atualizaSistema(sitemaSteps);
            triangLU(matrizL,matrizU,sitemaGauss);   
        }
        
        resolveLY(matrizL,y,sitemaSteps->deltaFuncoes,sitemaSteps->dimensao);
        resolveUX(matrizU,sitemaSteps->delta,y,sitemaSteps->dimensao);

        printf("%1.14e\t|", evaluator_evaluate(sitemaSteps->funcao,sitemaSteps->dimensao,sitemaSteps->nomesVariaveis,sitemaSteps->vtrVariaveis) );
        gstepsTempo=timestamp() - gstepsTempo;
        
        // gauss seidel
        gseidelTempo=timestamp();
        gaussSeidel(sistemaSeidel);
        gseidelTempo = timestamp() - gseidelTempo;
        printf("%1.14e\t\n", evaluator_evaluate(sistemaSeidel->funcao,sistemaSeidel->dimensao,sistemaSeidel->nomesVariaveis,sistemaSeidel->vtrVariaveis) );
        
        calculaProximoX(sitemaGauss);
        atualizaSistema(sitemaGauss);

        calculaProximoX(sitemaSteps);
        atualizaSistema(sitemaSteps);

        gaussNormaDeltaI=calculaNorma(sitemaGauss->delta,sitemaGauss->dimensao);
        gaussNormaDeltaF=calculaNorma(sitemaGauss->deltaFuncoes,sitemaGauss->dimensao);

        stepsNormaDeltaI=calculaNorma(sitemaSteps->delta,sitemaSteps->dimensao);
        stepsNormaDeltaF=calculaNorma(sitemaSteps->deltaFuncoes,sitemaSteps->dimensao);
       
        calculaProximoX(sistemaSeidel);
        atualizaSistema(sistemaSeidel);
        seidelNormaDeltaI=calculaNorma(sistemaSeidel->delta,sistemaSeidel->dimensao);
        seidelNormaDeltaF=calculaNorma(sistemaSeidel->deltaFuncoes,sistemaSeidel->dimensao);

       
        teste =verificaParada(gaussNormaDeltaI,gaussNormaDeltaF,stepsNormaDeltaI,stepsNormaDeltaI,seidelNormaDeltaF,seidelNormaDeltaF,DE->Tole_epsilon);
        
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
}
void atualizaSistema(SistemaL *SL){
    SL->matrizHessiana  = montamatriz(SL); 
    SL->deltaFuncoes    = montaDeltaF(SL); 
}

int verificaParada(long double gaussNormaDeltaI, long double gaussNormaDeltaF, long double stepsNormaDeltaI,
                long double stepsNormaDeltaF, long double seidelNormaDeltaI, long double seidelNormaDeltaF, long double epsilon){

    return (gaussNormaDeltaI > epsilon) &&  (gaussNormaDeltaF > epsilon) 
        && (stepsNormaDeltaI > epsilon) &&  (stepsNormaDeltaF > epsilon) 
        && (seidelNormaDeltaF > epsilon) &&  (seidelNormaDeltaI > epsilon);

}

void eliminacaoGauss(SistemaL *SL) {
  gtriang(SL->matrizHessiana,SL->deltaFuncoes,SL->dimensao);
  gretrossubs(SL->matrizHessiana,SL->delta,SL->deltaFuncoes,SL->dimensao);
}
void resolveLY(double **A,double *X,double *B,int tam){
    gretrossubsInf(A,X,B,tam);
};
void resolveUX(double **A,double *X,double *B,int tam){
    gretrossubs(A,X,B,tam);
};

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

void gpivot(double **A,double *B, int tam, int i) {
  double max = fabs(A[i][i]);
  int max_i = i;
  for (int j = i+1; j < tam; ++j) {
    double v = fabs(A[j][i]);
    if (v > max) {
      max = v;
      max_i = j;
    }
  }
  if (max_i != i) {
    double *tmp = A[i];
    A[i] = A[max_i];
    A[max_i] = tmp;

    double aux = B[i];
    B[i] = B[max_i];
    B[max_i] = aux;
  }
} 

void gretrossubs(double **A, double *X, double *B, int tam) {
  for (int i = tam-1; i >=0; --i) {
    X[i] = B[i];
    for (int j = i+1; j < tam; j++)
      X[i] -= A[i][j] * X[j];
    X[i] /= A[i][i];
  }
}

void gretrossubsInf(double **A, double *X, double *B, int tam) {
  for (int i = 0; i < tam; i++) {
    X[i] = B[i];
    for (int j = i-1; j >= 0; j--)
      X[i] -= A[i][j] * X[j];
    X[i] /= A[i][i];
  }
}
void gtriang(double **A,double *B,int tam) {
  for (int i = 0; i < tam; ++i) {
    gpivot(A,B,tam,i);
    for (int k = i+1; k < tam; ++k) {
      double m = A[k][i] / A[i][i];
      if (isnan(m))
        printf("ERRO: %g\n", A[i][i]);
      A[k][i] = 0.0;
      for (int j = i+1; j < tam; ++j)
        A[k][j] -= A[i][j] * m;
      B[k] -= B[i] * m;
    }
  }
} 