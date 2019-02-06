CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

unittest1: dominion.o unittest1.c
	gcc -o unittest1 -g dominion.c unittest1.c rngs.c $(CFLAGS)

unittest2: dominion.o unittest2.c
	gcc -o unittest2 -g dominion.c unittest2.c rngs.c $(CFLAGS)

unittest3: dominion.o unittest3.c
	gcc -o unittest3 -g dominion.c unittest3.c rngs.c $(CFLAGS)

unittest4: dominion.o unittest4.c
	gcc -o unittest4 -g dominion.c unittest4.c rngs.c $(CFLAGS)

cardtest1: dominion.o cardtest1.c
	gcc -o cardtest1 -g dominion.c cardtest1.c rngs.c $(CFLAGS)

cardtest2: dominion.o cardtest2.c
	gcc -o cardtest2 -g dominion.c cardtest2.c rngs.c $(CFLAGS)

cardtest3: dominion.o cardtest3.c
	gcc -o cardtest3 -g dominion.c cardtest3.c rngs.c $(CFLAGS)

cardtest4: dominion.o cardtest4.c
	gcc -o cardtest4 -g dominion.c cardtest4.c rngs.c $(CFLAGS)

unittestresults: dominion.o unittest1 unittest2 unittest3 unittest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unittest1 &> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	gcov -f -b -c dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe ????test?
