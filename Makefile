    CC     = gcc -g -std=c11
    CFLAGS = -Wall
    LFLAGS = -lm

      PROG = matrixInv
      OBJS = utils.o matriz.o argumentos.o

.PHONY: limpa faxina clean purge all

%.o: %.c %.h utils.h
	$(CC) -c $(CFLAGS) $<

$(PROG) : % :  $(OBJS) %.o
	$(CC) -o $@ $^ $(LFLAGS)

limpa clean:
	@rm -f *~ *.bak

faxina purge:   limpa
	@rm -f *.o core a.out
	@rm -f $(PROG)

