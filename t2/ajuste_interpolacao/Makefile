# Autores:
#   Jorge Lucas Vicilli Jabczenski
#     GRR20190372
#   Vinicius Tikara Venturi Date
#     GRR20190367  

    CC     = gcc -g -std=c11
    CFLAGS = -DLIKWID_PERFMON -I /home/soft/likwid/include -O3 -mavx -march=native 
    LFLAGS = -lm -L /home/soft/likwid/lib -llikwid

      PROG = inter_ajuste
      OBJS = utils.o matriz.o gauss.o interpolacao.o ajuste_curvas.o argumentos.o

.PHONY: clean all

%.o: %.c %.h 
	$(CC) -c $(CFLAGS) $<

$(PROG) : % :  $(OBJS) %.o
	$(CC) -o $@ $^ $(LFLAGS)

clean: 
	@rm -f *.o
	@rm -f $(PROG)
