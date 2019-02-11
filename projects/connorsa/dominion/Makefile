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

all: playdom player

## Added a cleanup for dSYM folder files
clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe ut1
	rm -rf badTestDrawCard.dSYM playdom.dSYM player.dSYM testDrawCard.dSYM ut1.dSYM ut2.dSYM

ct1: clean cardtest1.c dominion.o rngs.o
	gcc  -o ct1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

ct2: clean cardtest2.c dominion.o rngs.o
	gcc  -o ct2 -g cardtest2.c dominion.o rngs.o $(CFLAGS)

ct4: clean cardtest4.c dominion.o rngs.o
	gcc  -o ct4 -g cardtest4.c dominion.o rngs.o $(CFLAGS)

ut1: clean unittest1.c dominion.o rngs.o
	gcc  -o ut1 -g unittest1.c dominion.o rngs.o $(CFLAGS)

ut2: clean unittest2.c dominion.o rngs.o
	gcc  -o ut2 -g unittest2.c dominion.o rngs.o $(CFLAGS)

ut3: clean unittest3.c dominion.o rngs.o
	gcc  -o ut3 -g unittest3.c dominion.o rngs.o $(CFLAGS)

ut4: clean unittest4.c dominion.o rngs.o
	gcc  -o ut4 -g unittest4.c dominion.o rngs.o $(CFLAGS)

cov1: ut1
	./ut1
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output covhtml

cov2: ut2
	./ut2
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output covhtml

cov3: ut3
	./ut3
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output covhtml

cov4: ut4
	./ut4
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output covhtml

covc1: ct1
	./ct1
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output covhtml

covc2: ct2
	./ct2
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output covhtml
