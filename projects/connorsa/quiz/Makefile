testme.c.gcov: testme
	./testme || true
	gcov testme.c 
	
testme: testme.c
	gcc -o testme testme.c -coverage -fpic -lm

.PHONY: clean
clean: 
	rm -f testme testme.c.gcov testme.gcda testme.gcno


