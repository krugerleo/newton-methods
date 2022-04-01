    CC     = gcc -g
    CFLAGS = -g -std=c11
    LFLAGS = -Wl,-rpath -Wl, -lm

    PROG = teste
    OBJS = funcoes.o testeentrada.o

.PHONY: clean purge all

%.o: %.c
	$(CC) -c $(CFLAGS) $<

$(PROG):  $(OBJS) testeentrada.o
	$(CC) -o $@ $^ $(LFLAGS)

clean:
	@rm -f *~ *.bak

purge:   clean
	@rm -rf bin obj *.layout *.depend
	@rm -f *.o core a.out
	@rm -f $(PROG)
