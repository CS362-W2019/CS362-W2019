CFLAGS=-Wall -fpic --coverage -ftest-coverage -fprofile-arcs -lm -std=c99

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
	rm -f $(TESTS)

TESTS=$(patsubst %.c,%,$(wildcard unittest*.c) $(wildcard cardtest*.c))
define TESTRULE
$(test): $(test).c dominion.o rngs.o
	gcc -o $$@ -g $$^ $(CFLAGS)
endef
$(foreach test,$(TESTS),$(eval $(TESTRULE)))

unittestresults: $(TESTS)
	rm -f *.gcda *.gcno
	for t in $(TESTS); do ./$$t; done

