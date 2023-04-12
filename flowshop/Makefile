all: 3fss 3fss_gen

3fss: src/3fss.c src/3fss.h src/3fss_heuristic.c src/3fss_bruteforce.c
	gcc src/3fss.c src/3fss_heuristic.c src/3fss_bruteforce.c -o 3fss

3fss_gen: src/3fss_gen.c
	gcc src/3fss_gen.c -o 3fss_gen

clean:
	rm -f 3fss 3fss_gen test

test: all
	./3fss_gen 8 8 test && echo "--Input--" && cat test && echo "\n--Heuristic--" && ./3fss -h test && echo "\n--Bruteforce--" && ./3fss -b test