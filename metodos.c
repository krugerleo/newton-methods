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

/*long double calculoNormaDelta(double *delta, int n){
    long double soma,quadrado;
    soma=0;
    for(int i = 0;i<n;i++){
        quadrado = delta[i]*delta[i];
        soma = soma+quadrado;
    }
    
    return sqrt(soma);
}*/

void gaussSeidel(SistemaL *SL){
    int contador = 0;
    int n=SL->dimensao;
    double oldDelta[n];
    double parada[n];
   

    for (int i = 0; i < n; i++){
        oldDelta[i]=0;
    }
    parada[0] = 10;
    while (contador<50 && (calculaNorma(parada,n)>0.000001)) {
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
  
    double value;

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
    SistemaL *sistemaGauss;
    SistemaL *sistemaSteps;
    SistemaL *sistemaSeidel;
    
   // sistemaTempo=timestamp();
    // Aloca sistemas ()
    sistemaGauss = alocaSistemaLinear(DE->Qnt_variaveis);
    sistemaSteps = alocaSistemaLinear(DE->Qnt_variaveis);
    sistemaSeidel = alocaSistemaLinear(DE->Qnt_variaveis);    
    
    //fazer um vetor que guarda respostas
    max = calculaNorma(SL->vtrVariaveis,SL->dimensao);
    SL->matrizHessiana  = montamatriz(SL); 
    SL->deltaFuncoes    = montaDeltaF(SL);    
   // sistemaTempo=timestamp()-sistemaTempo;
    
    int x = 0;

    /*gaussNormaDeltaI=15;
    gaussNormaDeltaF=calculoNormaDelta(SL->deltaFuncoes,SL->dimensao);
    
    stepsNormaDeltaI=15;
    stepsNormaDeltaF=calculoNormaDelta(SL->deltaFuncoes,SL->dimensao);

    seidelNormaDeltaI=15;
    seidelNormaDeltaF=calculoNormaDelta(SL->deltaFuncoes,SL->dimensao);*/
    gaussNormaDeltaF=calculaNorma(SL->deltaFuncoes,SL->dimensao);
    gaussNormaDeltaI=15;
    stepsNormaDeltaI=15;
    seidelNormaDeltaI=15;
    
    stepsNormaDeltaF=gaussNormaDeltaF;
    seidelNormaDeltaF=gaussNormaDeltaF;

    // Copia ?
    copiaSistema(sistemaGauss,SL);
    copiaSistema(sistemaSeidel,SL);
    copiaSistema(sistemaSteps,SL);
    free(SL);

    int it = 2;
    int gausUltima = 1;
    int seidelUltima = 1;
    int stepsUltima = 1;

    double gaussTempoTotal = 0;
    double stepsTempoTotal = 0;
    double seidelTempoTotal = 0;

    double gaussMontaHessiana;
    double gaussTotalHessiana =0;
    
    double stepsMontaHessiana;
    double stepsTotalHessiana =0;

    double seidelMontaHessiana;
    double seidelTotalHessiana =0;

    printf("\nepisilon: %1.8Lf\n",DE->Tole_epsilon);
    printf("\n%s\n",DE->Funcao);
    printf("#Iteração\t| Newton Padrão\t\t| Newton Modificado\t| Newton Inexato\n");
    while ( (verificaParada(gaussNormaDeltaF,gausUltima,DE->Tole_epsilon,1) 
            || verificaParada(stepsNormaDeltaF,stepsUltima,DE->Tole_epsilon,2) 
            || verificaParada(seidelNormaDeltaF,seidelUltima,DE->Tole_epsilon,3)) 
            && (x <= *DE->Max_interacao) ){       
        printf("%d\t\t|",x);        
        
        //Gauss
        if( (gaussNormaDeltaF > DE->Tole_epsilon) && (gausUltima > 0) ){
            gaussTempo=timestamp();
            eliminacaoGauss(sistemaGauss);
            gaussTempo=timestamp() - gaussTempo;        
            gaussTempoTotal += gaussTempo;
            value =  evaluator_evaluate(sistemaGauss->funcao,sistemaGauss->dimensao,sistemaGauss->nomesVariaveis,sistemaGauss->vtrVariaveis);
            if(isnan(value)){
                printf("ERROR\t\t\t|");
                gausUltima = 0;
            }else{
                printf("%1.14e\t|", value);
            }

            gaussNormaDeltaF = calculaNorma(sistemaGauss->deltaFuncoes,sistemaGauss->dimensao);
            gaussNormaDeltaI = calculaNorma(sistemaGauss->delta,sistemaGauss->dimensao);
            gaussMontaHessiana=timestamp();
            calculaProximoX(sistemaGauss);
            atualizaSistema(sistemaGauss);
            gaussMontaHessiana = timestamp()-gaussMontaHessiana;
            gaussTotalHessiana += gaussMontaHessiana;
            if(gausUltima == 2)
                gausUltima = 0;                

                
            if( (gaussNormaDeltaI < DE->Tole_epsilon) && (gausUltima != 0) )
                gausUltima = 2;
            

            
        }else{
            printf("\t\t\t|" );
        }

        //Gauss Steps
        if( (stepsNormaDeltaF > DE->Tole_epsilon) && (stepsUltima > 0) ){
            gstepsTempo=timestamp();
            if( (x % it == 0) ){
                atualizaSistema(sistemaSteps);
                triangLU(matrizL,matrizU,sistemaSteps);   
            }
            
            resolveLY(matrizL,y,sistemaSteps->deltaFuncoes,sistemaSteps->dimensao);
            resolveUX(matrizU,sistemaSteps->delta,y,sistemaSteps->dimensao);
            
            value = evaluator_evaluate(sistemaSteps->funcao,sistemaSteps->dimensao,sistemaSteps->nomesVariaveis,sistemaSteps->vtrVariaveis);
            if(isnan(value)){
                printf("ERROR\t\t\t|");
                stepsUltima = 0;
            }else{
                printf("%1.14e\t|", value);
            }
            
            gstepsTempo=timestamp() - gstepsTempo;
            stepsTempoTotal+=gstepsTempo;

            stepsMontaHessiana=timestamp();
            calculaProximoX(sistemaSteps);
            stepsMontaHessiana = timestamp()-stepsMontaHessiana;
            stepsTotalHessiana += stepsMontaHessiana;

        

            if(stepsUltima == 2)
                stepsUltima = 0;                

            if( (stepsNormaDeltaI < DE->Tole_epsilon) && (stepsUltima != 0) )
                stepsUltima = 2;

        }else{
            printf("\t\t\t|" );
        }

        // gauss seidel
        if( (seidelNormaDeltaF > DE->Tole_epsilon) && (seidelUltima > 0) ){
            gseidelTempo=timestamp();
            gaussSeidel(sistemaSeidel);
            gseidelTempo = timestamp() - gseidelTempo;
            seidelTempoTotal+=gseidelTempo;
            value = evaluator_evaluate(sistemaSeidel->funcao,sistemaSeidel->dimensao,sistemaSeidel->nomesVariaveis,sistemaSeidel->vtrVariaveis);
            if(isnan(value)){
                printf("ERROR\t\t\t|");
                seidelUltima = 0;
            }else{
                printf("%1.14e\t|", value);
            }
            
            seidelNormaDeltaF=calculaNorma(sistemaSeidel->deltaFuncoes,sistemaSeidel->dimensao);
            seidelNormaDeltaI=calculaNorma(sistemaSeidel->delta,sistemaSeidel->dimensao);

           

            seidelMontaHessiana=timestamp();
            calculaProximoX(sistemaSeidel);
            atualizaSistema(sistemaSeidel);
            seidelMontaHessiana = timestamp()-seidelMontaHessiana;
            seidelTotalHessiana += seidelMontaHessiana;
            
            if(seidelUltima == 2)
                seidelUltima = 0;                

            if( (seidelNormaDeltaI < DE->Tole_epsilon) && (seidelUltima != 0) ){
                seidelUltima = 2;
            }
                

        }else{
            printf("\t\t\t|" );
        }

        printf("Norma F1: %1.8Lf Norma D1: %1.8Lf\t",gaussNormaDeltaF,gaussNormaDeltaI);
        printf("Norma F2: %1.8Lf Norma D2: %1.8Lf\t",stepsNormaDeltaF,stepsNormaDeltaI);
        printf("Norma F3: %1.8Lf Norma D3: %1.8Lf\n",seidelNormaDeltaF,seidelNormaDeltaI);
        x++;
    }
    printf("Tempo total \t| %1.14e\t| %1.14e\t| %1.14e  \n", gaussTempoTotal, stepsTempoTotal, seidelTempoTotal);
    //Usa a mesma variável pois é calculado uma vez no sistema.c
    //printf("Tempo derivadas | %1.14e\t| %1.14e\t| %1.14e \n", SL->tempoDerivadas, SL->tempoDerivadas, SL->tempoDerivadas);
    //Usa o mesmo valor pois o sistema é montado antes dos calculos
   // printf("Tempo SL \t| %1.14e\t| %1.14e\t| %1.14e \n", sistemaTempo, sistemaTempo, sistemaTempo);    
   
    printf("Tempo hessiana gauss = %1.14e\n",gaussTotalHessiana);
    printf("Tempo hessiana gauss = %1.14e\n",stepsTotalHessiana);
    printf("Tempo hessiana gauss = %1.14e\n",seidelTotalHessiana);
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

/*void confereSistemas(SistemaL *gauss, SistemaL *steps, SistemaL *seidel){
    printf("\nGAUSS\n");
    printMatrix(gauss->matrizHessiana,gauss->dimensao);
    printf("\nSTEPS\n");
    printMatrix(steps->matrizHessiana,steps->dimensao);
    printf("\nSEIDEL\n");
    printMatrix(seidel->matrizHessiana,seidel->dimensao);
}*/

/*void printMatrix(double** matrix, int tam){
    for (int row =0; row<tam; row++)
    {
        for(int columns=0; columns<tam; columns++)
        {
            printf("%p     ", &matrix[row][columns]);
        }
        printf("\n");
    }
}*/

void copiaSistema(SistemaL *copia, SistemaL *original){

    //     int dimensao;                   // dimensão do SL
    //     double tempoDerivadas;          // ?
    //     double *vtrVariaveis;           // vetor nxn de posições da matriz Guarda aproximação inicial
    //     void ***matrizHessianaEval;     // Matriz evaluator for hessiana
    //     void **vtrDerivadasEval;        // Vetor evaluator for Delta F
    //     char **nomesVariaveis;          // Nomes variaveis
    //     double **matrizHessiana;        // matrix hessiana com valores
    //     double *deltaFuncoes;           // vetor valores do delta das funções 
    //     double *delta;                  // vetor valores de delta
    //     void *funcao;                   // eval da função
        

    // Copia dimensao
    copia->dimensao = original->dimensao;
    // printf("Valor C: %d O: %d EC: %p EO: %p\n",copia->dimensao, original->dimensao, &copia->dimensao, &original->dimensao);
    // tempoDerivadas não precisa
    // copia vtrVariaveis
    for(int i = 0; i < original->dimensao; i++){
        copia->vtrVariaveis[i] = original->vtrVariaveis[i];
        // printf("Valor C[%d]: %f O: %f EC: %p EO: %p\n",i,copia->vtrVariaveis[i], original->vtrVariaveis[i], &copia->vtrVariaveis[i], &original->vtrVariaveis[i]);    
    }
    // copia de endereço
    copia->matrizHessianaEval = original->matrizHessianaEval;
    copia->vtrDerivadasEval = original->vtrDerivadasEval;
    copia->nomesVariaveis = original->nomesVariaveis;
    copia->vtrDerivadasEval = original->vtrDerivadasEval;
    // Copia em endereço novo
    for (int i = 0; i < original->dimensao; i++)
    {
        for (int j = 0; j < original->dimensao; j++)
        {
            copia->matrizHessiana[i][j] = original->matrizHessiana[i][j];
            // printf("Valor C[%d][%d]: %f O: %f EC: %p EO: %p\n",i,j,copia->matrizHessiana[i][j], original->matrizHessiana[i][j], &copia->matrizHessiana[i][j], &original->matrizHessiana[i][j]);    
        }
    }
    // Copia em endereço novo
    for(int i = 0; i < original->dimensao; i++){
        copia->deltaFuncoes[i] = original->deltaFuncoes[i];
        // printf("Valor C[%d]: %f O: %f EC: %p EO: %p\n",i,copia->deltaFuncoes[i], original->deltaFuncoes[i], &copia->deltaFuncoes[i], &original->deltaFuncoes[i]);    
    }
    // Copia em endereço novo
    for(int i = 0; i < original->dimensao; i++){
        copia->delta[i] = original->delta[i];
        // printf("Valor C[%d]: %f O: %f EC: %p EO: %p\n",i,copia->delta[i], original->delta[i], &copia->delta[i], &original->delta[i]);    
    }
    // Copia de endereço
    copia->funcao = original->funcao;    
}

int verificaParada(long double normaDeltaF,int ultima, long double epsilon, int met){
    // retorna 1 para continuar ou 0 para parar
    
    // if((ultima == 0)){
    //     printf("metodo %d parou por ultima\n",met);
    // }else if((normaDeltaF < epsilon)){
    //     printf("metodo %d parou por deltaF\n",met);
    return !( (normaDeltaF < epsilon) ||  (ultima == 0) );

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
    for (int i = 0; i < SL->dimensao; i++)
    {
        for (int j = 0; j < SL->dimensao; j++)
        {
            U[i][j] = SL->matrizHessiana[i][j];
        }
    }
    
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