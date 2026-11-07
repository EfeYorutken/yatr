main:
	g++ -o yet_another_tetris_replica -std=c++23 main.cpp

run:
	g++ -o yet_another_tetris_replica -std=c++23 main.cpp
	./yet_another_tetris_replica 
	rm ./yet_another_tetris_replica 

debug:
	g++ -g -o debug -std=c++23 main.cpp
