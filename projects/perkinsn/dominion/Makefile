CC="/usr/local/Cellar/gcc/8.2.0/bin/gcc-8"
GCOV="/usr/local/Cellar/gcc/8.2.0/bin/gcov-8"

CFLAGS=-Wall -fpic -std=c99 -MMD -MP -fprofile-arcs -ftest-coverage 
SRCS=cards.c dominion.c interface.c rngs.c
OBJS=$(SRCS:.c=.o)
BINARIES=playdom player testDrawCard badTestDrawCard testBuyCard

.PHONY=all
all: $(BINARIES)

$(BINARIES): % : %.c $(OBJS)
	echo $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ 

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
