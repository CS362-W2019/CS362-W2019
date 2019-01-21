# modify these variables to point to gcc and gcov
CC="/usr/local/Cellar/gcc/8.2.0/bin/gcc-8"
GCOV="/usr/local/Cellar/gcc/8.2.0/bin/gcov-8"
CFLAGS=-Wall -fpic -std=c99 -MMD -MP -fprofile-arcs -ftest-coverage 

# modify these variables as source/binary files are added or removed
SRCS=cards.c dominion.c interface.c rngs.c
OBJS=$(SRCS:.c=.o)
TESTS=testDrawCard testBuyCard testShuffle testInit
BINARIES=$(TESTS) playdom player

# default action to build all binaries
.PHONY=all
all: $(BINARIES)

# compiles all the binaries and generates dependencies
$(BINARIES): % : %.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ 

# build all the generated dependencies
-include $(wildcard *.d)

.PHONY=runtests
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

.PHONY=clean
clean:
	rm -f *.o *.exe *.gcov *.gcda *.gcno *.so *.out *.d
	rm -rf *.dSYM
	rm -f playdom player testDrawCard badTestDrawCard testBuyCard testInit testShuffle
