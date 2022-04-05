parametrosCompilacao=-Wall -lpthread
nomeAula=newtonMethdods

all: $(nomeAula)

$(nomeAula): main.o dados.o sistema.o
	gcc -o $(nomeAula) main.o dados.o sistema.o -I/usr/local/include -L/usr/local/lib -lmatheval $(parametrosCompilacao)


dados.o: dados.h dados.c
	gcc -c dados.c $(parametrosCompilacao)

sistema.o: sistema.h sistema.c
	gcc -c sistema.c $(parametrosCompilacao)

# metodos.o: metodos.h metodos.c
# 	gcc -c metodos.c $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomeAula)
