lab9: game.o physics.o renderer.o main.o
	g++ main.o renderer.o game.o physics.o -o lab9 -lX11
main.o: main.cpp game.h renderer.h renderer.cpp game.cpp
	g++ -c main.cpp -o main.o
game.o: game.cpp game.h renderer.h physics.h physics.cpp renderer.cpp
	g++ -c game.cpp -o game.o	
renderer.o: renderer.cpp renderer.h physics.h physics.cpp
	g++ -c renderer.cpp -o renderer.o
physics.o: physics.cpp physics.h
	g++ -c physics.cpp -o physics.o
