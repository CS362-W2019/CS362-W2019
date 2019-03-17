CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

# unittest1, unittest2, unittest3, unittest4
unittest1: unittest1.c dominion.o rngs.o
	gcc -o unittest1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

unittest2: unittest2.c dominion.o rngs.o
	gcc -o unittest2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

unittest3: unittest3.c dominion.o rngs.o
	gcc -o unittest3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

unittest4: unittest4.c dominion.o rngs.o
	gcc -o unittest4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

# cardtest1, cardtest2, cardtest3, cardtest4
cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest3.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

randomtestcard1.out: dominion.o
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestcard1 > randomtestcard1.out
	gcov -c -b randomtestcard1.c >> randomtestcard1.out
	gcov -c -b dominion.c >> randomtestcard1.out
	cat randomtestcard1.c.gcov >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: dominion.o
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestcard2 > randomtestcard2.out
	gcov -c -b  randomtestcard2.c >> randomtestcard2.out
	gcov -c -b  dominion.c >> randomtestcard2.out
	cat randomtestcard2.c.gcov >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

randomtestadventurer.out: dominion.o
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)
	./randomtestadventurer > randomtestadventurer.out
	gcov -c -b randomtestadventurer.c >> randomtestadventurer.out
	gcov -c -b  dominion.c >> randomtestadventurer.out
	cat randomtestadventurer.c.gcov >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out


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

all: playdom player 

unittest: unittest1 unittest2 unittest3 unittest4

cardtest: cardtest1 cardtest2 cardtest3 cardtest4

unittestresults.out: all unittest cardtest
	./unittest1 &> unittestresults.out
	./unittest2 &>> unittestresults.out
	./unittest3 &>> unittestresults.out
	./unittest4 &>> unittestresults.out
	./cardtest1 &>> unittestresults.out
	./cardtest2 &>> unittestresults.out
	./cardtest3 &>> unittestresults.out
	./cardtest4 &>> unittestresults.out
	gcov -b unittest1.c >> unittestresults.out
	cat unittest1.c.gcov >> unittestresults.out
	gcov -b unittest2.c >> unittestresults.out
	cat unittest2.c.gcov >> unittestresults.out
	gcov -b unittest3.c >> unittestresults.out
	cat unittest3.c.gcov >> unittestresults.out
	gcov -b unittest4.c >> unittestresults.out
	cat unittest4.c.gcov >> unittestresults.out
	gcov -b cardtest1.c >> unittestresults.out
	cat cardtest1.c.gcov >> unittestresults.out
	gcov -b cardtest2.c >> unittestresults.out
	cat cardtest2.c.gcov >> unittestresults.out
	gcov -b cardtest3.c >> unittestresults.out
	cat cardtest3.c.gcov >> unittestresults.out
	gcov -b cardtest4.c >> unittestresults.out
	cat cardtest4.c.gcov >> unittestresults.out
	gcov -b dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
