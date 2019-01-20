# modify these variables to point to gcc and gcov
CC="/usr/local/Cellar/gcc/8.2.0/bin/gcc-8"
GCOV="/usr/local/Cellar/gcc/8.2.0/bin/gcov-8"
CFLAGS=-Wall -fpic -std=c99 -MMD -MP -fprofile-arcs -ftest-coverage 

# modify these variables as source files are added or removed
SRCS=cards.c dominion.c interface.c rngs.c
OBJS=$(SRCS:.c=.o)
BINARIES=playdom player testDrawCard badTestDrawCard testBuyCard

# default action
.PHONY=all
all: $(BINARIES)

# compiles all the binaries and generates dependencies
$(BINARIES): % : %.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ 

# using the -MMD and -MP flags will automatically create .d files for
# all the dependencies.
# this line includes those .d files to build them.
-include $(wildcard *.d)

.PHONY=runtests
runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	$(GCOV) dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

.PHONY=clean
clean:
	rm -f *.o *.exe *.gcov *.gcda *.gcno *.so *.out *.d
	rm -rf *.dSYM
	rm -f playdom player testDrawCard badTestDrawCard testBuyCard
