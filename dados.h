#ifndef DADOSENTRADA_H
#define DADOSENTRADA_H

#define ncaracteres  1000

typedef struct {
    int Qnt_variaveis;
    char *Funcao;
    double *Ap_inicial;
    long double Tole_epsilon;
    int *Max_interacao;
} DadosE;

DadosE *lerDados();

DadosE *alocaDados(unsigned int n);

void imprimeDados(DadosE *DE);

#endif
