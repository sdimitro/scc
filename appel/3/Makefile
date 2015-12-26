CC=gcc
CC_OPTS=-Wall -Wextra -g
CC_EOPTS=-Wpedantic -std=c11 -lfl -ly

#LEX=lex
LEX=flex

YACC=yacc
#YACC=bison

parsetest: parsetest.o y.tab.o lex.yy.o errormsg.o util.o
	$(CC) -o parsetest -g parsetest.o y.tab.o lex.yy.o errormsg.o util.o

lextest: driver.o lex.yy.o errormsg.o util.o y.tab.o
	$(CC) -g -o lextest driver.o lex.yy.o errormsg.o util.o y.tab.o

parsetest.o: parsetest.c errormsg.h util.h
	$(CC) $(CC_OPTS) $(CC_EOPTS) -c parsetest.c

driver.o: driver.c y.tab.h errormsg.h util.h
	$(CC) $(CC_OPTS) $(CC_EOPTS) -c driver.c

errormsg.o: errormsg.c errormsg.h util.h
	$(CC) $(CC_OPTS) $(CC_EOPTS) -c errormsg.c

lex.yy.o: lex.yy.c y.tab.h errormsg.h util.h
	$(CC) $(CC_OPTS) $(CC_EOPTS) -c lex.yy.c

lex.yy.c: tiger.l y.tab.h
	$(LEX) tiger.l

y.tab.h: y.tab.c
	echo "y.tab.h was created at the same time as y.tab.c"

y.tab.o: y.tab.c
	$(CC) $(CC_OPTS) $(CC_EOPTS) -c y.tab.c

y.tab.c: tiger.y
	$(YACC) -dv tiger.y

util.o: util.c util.h
	$(CC) $(CC_OPTS) $(CC_EOPTS) -c util.c

clean: 
	rm -f parsetest lextest util.o parsetest.o driver.o lex.yy.o errormsg.o y.tab.c y.tab.h y.tab.o
