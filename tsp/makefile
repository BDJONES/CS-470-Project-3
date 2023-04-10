bfm: bfm.o
	g++ bfm.o -o bfm

heuristic: heuristic.o
	g++ heuristic.o -o heuristic

bfm.o: brute_force.cpp
	g++ -c brute_force.cpp -o bfm.o

heuristic.o: heuristic.cpp
	g++ -c heuristic.cpp

target: dependancies
	action

clean:
	rm *.o bfm heuristic

run: bfm heuristic
	./bfm test1.dat
	./bfm test2.dat
	./heuristic test1.dat
	./heuristic test2.dat
	# ./heuristic test4.dat

