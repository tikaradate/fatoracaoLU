# Autores:
#   Jorge Lucas Vicilli Jabczenski
#     GRR20190372
#   Vinicius Tikara Venturi Date
#     GRR20190367  

    CC     = gcc -g -std=c11
    CFLAGS = -Wall -O3 -mavx2
    LFLAGS = -lm

      PROG = inter_ajuste
      OBJS = utils.o matriz.o gauss.o interpolacao.o ajuste_curvas.o

.PHONY: clean all

%.o: %.c %.h utils.h
	$(CC) -c $(CFLAGS) $<

$(PROG) : % :  $(OBJS) %.o
	$(CC) -o $@ $^ $(LFLAGS)

clean: 
	@rm -f *.o
	@rm -f $(PROG)