#include <stdio.h>
#include <stdlib.h>
#include "testeentrada.h"
#include "funcoes.h"
#define ncaracteres  1000


int main(int argc, char const *argv[]){
    Sistema_Linear *SL;
    int i=0;
    printf("funcionou");
    while (SL = lerSistema()) {
        printf("%d",SL->Qnt_variaveis);
        printf("%s",SL->Funcao);
        printf("%lf",SL->Ap_inicial);
    }
}