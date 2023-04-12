all: 3dm 3dm_gen

3dm: src/3dm.cpp src/3dm.h src/3dm_heuristic.cpp src/3dm_bruteforce.cpp
	g++ src/3dm.cpp src/3dm_heuristic.cpp src/3dm_bruteforce.cpp -o 3dm

3dm_gen: src/3dm_gen.cpp
	g++ src/3dm_gen.cpp -o 3dm_gen

clean:
	rm -f 3dm 3dm_gen test

test: all
	./3dm_gen 10 5 test && echo "--Input--" && cat test && echo "\n--Heuristic--" && ./3dm -h test && echo "\n--Bruteforce--" && ./3dm -b test