#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dados.h"
#include "utils.h"
#include "sistema.h"
#include "metodos.h"

int main(int argc, char const *argv[]){
  double Tempototal;
  Tempototal=timestamp();
  DadosE *dadosEntrada;
  SistemaL *sistemaLinear;
  dadosEntrada = NULL;

//  If for saida padrão ou arquivo especificado
//  int temarq=0;
//  if(argv[1]!= NULL){
//    temarq=1;
//  }

  while ( (dadosEntrada = lerDados()) ) {
    sistemaLinear = criaSistemaLinear(dadosEntrada);
    newton(sistemaLinear, dadosEntrada);

    free(dadosEntrada);
   // freeSistemaLinear(sistemaLinear);
  }

  printf("\nFinalizou graciosamente\n");
  Tempototal=timestamp()-Tempototal;
  printf("Tempo total = %1.14e\n",Tempototal);
  return 0;

}