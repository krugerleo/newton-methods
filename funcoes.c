#include <stdio.h>
#include <stdlib.h>
#include "testeentrada.h"
#include "funcoes.h"


Sistema_Linear *alocaSistemaLinear(unsigned int n){
    //printf("entra aloca\n");
    Sistema_Linear *SL = (Sistema_Linear *) malloc(sizeof(Sistema_Linear));
    SL->Qnt_variaveis = n;
    SL->Funcao=(char *)malloc(sizeof(char *)*n);
    SL->Ap_inicial=(double *)malloc((sizeof(double *)*n));
    SL->Tole_epsilon=(double *)malloc((sizeof(double *)*n));
    SL->Max_interacao=(double *)malloc((sizeof(double *)*n));
   /* double *Ap_inicial;
    double *Tole_epsilon;
    double *Max_interacao;
    //printf("%d",SL->Qnt_variaveis);
*/
    return SL;
}
Sistema_Linear *lerSistema(){
   
    unsigned n;
   // Sistema_Linear *SL = (Sistema_Linear *) malloc(sizeof(Sistema_Linear));
    Sistema_Linear *SL = NULL;
    
    if (scanf("%d",&n) != EOF) {  
      
        SL = alocaSistemaLinear(n);
      /* if (!SL) return NULL;
        
        for(int i = 0; i < n; ++i)
            for(int j = 0; j < n; ++j)
                scanf("%lf", &(SL->A[i][j]));
        
        for(int i = 0; i < n; ++i)
            scanf("%lf", &(SL->b[i]));
        */
  }
    
    
    
    //scanf("%d",SL->Qnt_variaveis);
    //scanf("%s",SL->Funcao);
    //scanf("%lf",SL->Ap_inicial);
    return SL;
}