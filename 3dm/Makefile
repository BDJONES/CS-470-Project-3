all: 3dm 3dm_gen 3sat_gen 3sat23dm

3dm: src/3dm.cpp src/3dm.h src/3dm_heuristic.cpp src/3dm_bruteforce.cpp
	g++ src/3dm.cpp src/3dm_heuristic.cpp src/3dm_bruteforce.cpp -o 3dm

3dm_gen: src/3dm_gen.cpp
	g++ src/3dm_gen.cpp -o 3dm_gen

3sat_gen: src/3sat_gen.cpp
	g++ src/3sat_gen.cpp -o 3sat_gen

3sat23dm: ../mappings/3sat23dm.cpp
	g++ ../mappings/3sat23dm.cpp -o 3sat23dm

clean:
	rm -f 3dm 3dm_gen 3sat_gen 3sat23dm

test_3sat23dm: all
	./3sat_gen 3 2 3sat.dat && ./3sat23dm 3sat.dat 3dm.dat && echo "--3sat--" && cat 3sat.dat && echo "--3dm--" && cat 3dm.dat && echo "\n--Heuristic--" && ./3dm -h 3dm.dat && echo "\n--Bruteforce--" && ./3dm -b 3dm.dat && rm 3dm.dat 3sat.dat

test: all
	./3dm_gen 30 30 test.dat && echo "\n--3dm--" && cat test.dat && echo "\n--Heuristic--" && ./3dm -h test.dat && echo "\n--Bruteforce--" && ./3dm -b test.dat && rm test.dat