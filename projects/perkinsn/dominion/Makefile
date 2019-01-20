CFLAGS= -Wall -fpic -coverage -std=c99

.PHONY=all
all: playdom

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g $(CFLAGS)

dominion.o: dominion.h dominion.c
	gcc -c dominion.c -g $(CFLAGS)

cards.o: cards.c cards.h dominion.h
	gcc -c $< -g $(CFLAGS)

playdom: dominion.o playdom.c rngs.o cards.o
	gcc -o playdom playdom.c -g dominion.o rngs.o cards.o $(CFLAGS)

#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o cards.o rngs.o
	gcc -o player player.c -g cards.o dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o *.exe *.gcov *.gcda *.gcno *.so *.out
	rm -rf *.dSYM
	rm -f playdom player testDrawCard badTestDrawCard
