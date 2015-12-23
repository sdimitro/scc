CC=gcc
CC_OPTS=-Wall -Wextra -g
CC_EOPTS=-Wpedantic -std=c11

LEX=flex # TODO: what about plain lex?

lextest: driver.o lex.yy.o errormsg.o util.o
	$(CC) -g -o lextest driver.o lex.yy.o errormsg.o util.o

driver.o: driver.c tokens.h errormsg.h util.h
	$(CC) $(CC_OPTS) $(CC_EOPTS) -c driver.c

errormsg.o: errormsg.c errormsg.h util.h
	$(CC) $(CC_OPTS) $(CC_EOPTS) -c errormsg.c

# $(CC) $(CC_OPTS) $(CC_EOPTS) -c lex.yy.c :TODO:
lex.yy.o: lex.yy.c tokens.h errormsg.h util.h
	$(CC) -g -c lex.yy.c

lex.yy.c: tiger.lex
	flex tiger.lex

util.o: util.c util.h
	$(CC) $(CC_OPTS) $(CC_EOPTS) -c util.c

clean: 
	rm -f a.out util.o driver.o lex.yy.o lex.yy.c errormsg.o
