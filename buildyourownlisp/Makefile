CC = cc
CFLAGS= -Wall -g
program: parsing.c mpc.c
KEEP= Makefile $(wildcard *.c) $(wildcard *.h)
clean:
	rm -rf $(filter-out $(KEEP),$(wildcard *))

