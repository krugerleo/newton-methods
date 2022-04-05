#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"
#include "funcoes.h"
#include <matheval.h>
#include <assert.h>
#include "metodo.h"

#ifdef DEBUG
# define DEBUG_PRINT(x) printf x
#else
# define DEBUG_PRINT(x) do {} while (0)
#endif



int main(int argc, char const *argv[]){
  Dados_Entrada *DE;
  SistemaL *Novo_DE;
  DE = NULL;
  int i=0;
  int temarq=0;
  int teste;
  if(argv[1]!= NULL){
    temarq=1;
  }
 
  while (DE = lerDados()) {

    Novo_DE = converteMatriz(DE);
    free(DE);
  }
  printf("finalizou\n");
}