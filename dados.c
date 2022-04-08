#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "utils.h"
#include "dados.h"



DadosE *alocaDados(unsigned int n){

    DadosE *DE = (DadosE *) malloc(sizeof(DadosE));
    DE->Qnt_variaveis = n;
    DE->Funcao=(char *)malloc(sizeof(char *)*ncaracteres);
    DE->Ap_inicial=(double *)malloc((sizeof(double *)*n));
    DE->Tole_epsilon;//=(long double )malloc(sizeof(long double ));
    DE->Max_interacao=(int *)malloc(sizeof(int *));
    return DE;
}
DadosE *lerDados(){
   
    unsigned int n;
    DadosE *DE = NULL;
    
    if (scanf("%d",&n) != EOF) {  
        DE = alocaDados(n);

        scanf("%s",DE->Funcao);
        for(int i = 0; i < n; ++i){
              scanf("%lf",&DE->Ap_inicial[i]);
        };
        scanf("%Lf",&DE->Tole_epsilon);
        scanf("%d",DE->Max_interacao);
    }

    return DE;
}

void imprimeDados(DadosE *DE){
    printf("\nQuantidade de variaveis: %d\n",DE->Qnt_variaveis);
    printf("Função: %s\n",DE->Funcao);
    for(int i = 0; i < DE->Qnt_variaveis; ++i){
        printf("AP da variavel X%d: %lf\n",i,DE->Ap_inicial[i]);
    };
    printf("Epsilon: %Le\n",DE->Tole_epsilon);
    printf("Máximo Iterações: %d\n",*DE->Max_interacao);
};