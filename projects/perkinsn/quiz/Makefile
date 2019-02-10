all: testme testme.c.gcov

testme: testme.c
	gcc -Wall -std=c99 -fprofile-arcs -ftest-coverage $^ -o $@

testme.c.gcov: testme testme.c test
	gcov -b testme.c

.PHONY=test
test: testme
	-./testme

.PHONY=clean
clean:
	rm -rf *.dSYM/
	rm -f testme.c.gcov
	rm -f testme.gcda
	rm -f testme.gcno
	rm -f testme
