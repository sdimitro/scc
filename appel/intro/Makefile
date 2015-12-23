CC=gcc
CC_OPTS=-Wall -Wextra -g
CC_EOPTS=-Wpedantic -std=c11

a.out: main.o prog1.o slp.o util.o table.o
	cc -g main.o prog1.o slp.o util.o table.o

main.o: main.c slp.h util.h table.h
	$(CC) $(CC_OPTS) $(CC_EOPTS) -c main.c 

prog1.o: prog1.c slp.h util.h
	$(CC) $(CC_OPTS) $(CC_EOPTS) -c prog1.c 

slp.o: slp.c slp.h util.h
	$(CC) $(CC_OPTS) $(CC_EOPTS) -c slp.c 

table.o: table.c table.h util.h
	$(CC) $(CC_OPTS) $(CC_EOPTS) -c table.c 

util.o: util.c util.h
	$(CC) $(CC_OPTS) $(CC_EOPTS) -c util.c 

clean: 
	rm -f a.out util.o prog1.o slp.o main.o
