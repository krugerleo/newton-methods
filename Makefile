FLAGS	= -L /lib64 -lm -llikwid

LIK = -L${LIKWID_LIB}
nomeAula=newtonPC

all: $(nomeAula)

$(nomeAula): main.o dados.o sistema.o metodos.o utils.o Rosenbrock.o
	gcc -o $(nomeAula) main.o dados.o sistema.o metodos.o utils.o Rosenbrock.o -I/usr/local/include -L/usr/local/lib -L${LIK} $(FLAGS)

Rosenbrock.o: Rosenbrock.c Rosenbrock.h
	gcc -c Rosenbrock.c $(FLAGS)

utils.o: utils.c utils.h
	gcc -c utils.c $(FLAGS)


metodos.o: metodos.h metodos.c
	gcc -c metodos.c $(FLAGS)

dados.o: dados.h dados.c
	gcc -c dados.c $(FLAGS)

sistema.o: sistema.h sistema.c
	gcc -c sistema.c $(FLAGS)

# metodos.o: metodos.h metodos.c
# 	gcc -c metodos.c $(FLAGS)

main.o: main.c
	gcc -c main.c $(FLAGS)

clean:
	rm -f *.o *.gch $(nomeAula)
