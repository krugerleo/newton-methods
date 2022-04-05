#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dados.h"
#include "sistema.h"

SistemaL *alocaSistemaLinear(unsigned int n){

    SistemaL *SL= (SistemaL *) malloc(sizeof(SistemaL));
    SL->Dimensao = n;
    SL->VetorM = (double *)malloc((sizeof(double *)*n));
    SL->Mcoeficientes = (double **)malloc((sizeof(double **)*(n*n)));
    SL->Termos_Independentes = (double *)malloc((sizeof(double *)*n));
    return SL;
}
SistemaL *criaSistemaLinear(DadosE *DE){
    SistemaL *sistemaLinear = NULL;

    sistemaLinear = alocaSistemaLinear(DE->Qnt_variaveis);
    // TO DO CRIAR SISTEMA COM VALOROEES

    return sistemaLinear;
}