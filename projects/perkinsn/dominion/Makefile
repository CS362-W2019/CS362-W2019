# modify these variables to point to gcc and gcov
CC=gcc
GCOV=gcov
CFLAGS=-Wall -lm -fpic -std=c99 -MMD -MP -fprofile-arcs -ftest-coverage 

# modify these variables as source/binary files are added or removed
SRCS=cards.c dominion.c interface.c rngs.c test_helpers.c
OBJS=$(SRCS:.c=.o)
TESTS=testDrawCard testBuyCard testShuffle testInit
UNITTESTS=unittest1 unittest2 unittest3 unittest4
RANDOMTESTS=randomtestcard1 randomtestcard2 randomtestadventurer
CARDTESTS=cardtest1 cardtest2 cardtest3 cardtest4
BINARIES=$(TESTS) $(UNITTESTS) $(CARDTESTS) $(RANDOMTESTS) playdom player

# default action to build all binaries
.PHONY: all
all: $(BINARIES)

# compiles all the binaries and generates dependencies
$(BINARIES): % : %.c $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# build all the generated dependencies
-include $(wildcard *.d)

.PHONY: runtests
runtests: $(TESTS)
	rm -f unittestresult.out
	./testBuyCard  >> unittestresult.out
	echo >> unittestresult.out
	./testDrawCard >> unittestresult.out
	echo >> unittestresult.out
	./testShuffle  >> unittestresult.out
	echo >> unittestresult.out
	./testInit -1  >> unittestresult.out
	echo >> unittestresult.out
	$(GCOV) dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

.PHONY: unittestresults
unittestresults: $(UNITTESTS) $(CARDTESTS) $(OBJS) $(SRCS)
	rm -f unittestresults.out
	./unittest1 >> unittestresults.out
	./unittest2 >> unittestresults.out
	./unittest3 >> unittestresults.out
	./unittest4 >> unittestresults.out
	./cardtest1 >> unittestresults.out
	./cardtest2 >> unittestresults.out
	./cardtest3 >> unittestresults.out
	./cardtest4 >> unittestresults.out
	$(GCOV) dominion.c -bf >> unittestresults.out
	$(GCOV) cards.c -bf >> unittestresults.out

.PHONY: randomtestresults
randomtestresults: randomtestcard1.out randomtestcard2.out randomtestadventurer.out

randomtestcard1.out: randomtestcard1
	./$^ > $@
	$(GCOV) cards.c -bf >> $@

randomtestcard2.out: randomtestcard2
	./$^ > $@
	$(GCOV) cards.c -bf >> $@

randomtestadventurer.out: randomtestadventurer
	./$^ > $@
	$(GCOV) cards.c -bf >> $@

.PHONY: clean
clean:
	rm -f *.o *.exe *.gcov *.gcda *.gcno *.so *.out *.d
	rm -rf *.dSYM
	rm -f $(BINARIES)
