CFLAGS = -Wall -fpic -coverage -lm

testme: testme.c
	gcc -std=c99 -o testme -g  testme.c $(CFLAGS)
	./testme

clean:
	-rm -f *.gcda *.gcno testme