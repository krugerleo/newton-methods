parametrosCompilacao=-Wall -lpthread
nomeAula=NewtonPC

all: $(nomeAula)

$(nomeAula): main.o funcoes.o 
	gcc -o $(nomeAula) main.o funcoes.o -I/usr/local/include -L/usr/local/lib -lmatheval $(parametrosCompilacao)


funcoes.o: funcoes.h funcoes.c
	gcc -c funcoes.c $(parametrosCompilacao)

testeentrada.o: main.h main.c
	gcc -c main.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomeAula)
