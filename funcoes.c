#include <stdio.h>
#include <stdlib.h>
#include "testeentrada.h"
#include "funcoes.h"

Sistema_Linear *lerSistema(){
    Sistema_Linear *SL = (Sistema_Linear *) malloc(sizeof(Sistema_Linear));
    SL = NULL;
    scanf("%d",SL->Qnt_variaveis);
    scanf("%s",SL->Funcao);
    scanf("%lf",SL->Ap_inicial);
    return SL;
}