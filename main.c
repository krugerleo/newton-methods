#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "funcoes.h"
#include <matheval.h>
#include <assert.h>
#define ncaracteres  1000


int main(int argc, char const *argv[]){
  Sistema_Linear *SL;
  SistemaL_Convertido *Novo_SL;
  SL = NULL;
  int i=0;
  int temarq=0;
  int teste;
  if(argv[1]!= NULL){
    temarq=1;
  }
 
  while (SL = lerSistema()) {

    Novo_SL = converteMatriz(SL);

    
    free(SL);
  }
  printf("finalizou\n");
}