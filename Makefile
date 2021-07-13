# Autores:
#   Jorge Lucas Vicilli Jabczenski
#     GRR20190372
#   Vinicius Tikara Venturi Date
#     GRR20190367  

    CC     = gcc -g -std=c11 -g
    CFLAGS = -Wall
    LFLAGS = -lm

      PROG = matrixInv
      OBJS = utils.o matriz.o argumentos.o gauss.o

.PHONY: limpa faxina clean purge all

%.o: %.c %.h utils.h
	$(CC) -c $(CFLAGS) $<

$(PROG) : % :  $(OBJS) %.o
	$(CC) -o $@ $^ $(LFLAGS)

limpa clean:
	@rm -f *~ *.bak

faxina purge:	limpa
	@rm -f *.o core a.out
	@rm -f $(PROG)