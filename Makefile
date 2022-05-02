FLAGS	= -L /lib64 -lm
LIBS	= -lmatheval
nomeAula=newtonPC

all: $(nomeAula)

$(nomeAula): main.o dados.o sistema.o metodos.o utils.o
	gcc -O3 -mavx -march=native $(nomeAula) main.o dados.o sistema.o metodos.o utils.o -I/usr/local/include -L/usr/local/lib $(LIBS) $(FLAGS)


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
