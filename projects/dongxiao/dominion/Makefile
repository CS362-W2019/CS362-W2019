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

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)
test_unittest1: unittest1
	./unittest1
	gcov -b dominion.c

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)
test_unittest2: unittest2
	./unittest2
	gcov -b dominion.c

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)
test_unittest3: unittest3
	./unittest3
	gcov -b dominion.c

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)
test_unittest4: unittest4
	./unittest4
	gcov -b dominion.c

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)
test_cardtest1: cardtest1
	./cardtest1
	gcov -b dominion.c

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)
test_cardtest2: cardtest2
	./cardtest2
	gcov -b dominion.c

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)
test_cardtest3: cardtest3
	./cardtest3
	gcov -b dominion.c

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)
test_cardtest4: cardtest4
	./cardtest4
	gcov -b dominion.c

unittestresults: 
	make test_unittest1 1> unittestresults.out
	cat dominion.c.gcov 1>> unittestresults.out
	make test_unittest2 1>> unittestresults.out
	cat dominion.c.gcov 1>> unittestresults.out
	make test_unittest3 1>> unittestresults.out
	cat dominion.c.gcov 1>> unittestresults.out
	make test_unittest4 1>> unittestresults.out
	cat dominion.c.gcov 1>> unittestresults.out
	make test_cardtest1 1>> unittestresults.out
	cat dominion.c.gcov 1>> unittestresults.out
	make test_cardtest2 1>> unittestresults.out
	cat dominion.c.gcov 1>> unittestresults.out
	make test_cardtest3 1>> unittestresults.out
	cat dominion.c.gcov 1>> unittestresults.out
	make test_cardtest4 1>> unittestresults.out
	cat dominion.c.gcov 1>> unittestresults.out

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
