all: mygame

mygame: main.o snake_file.o
	g++ main.o snake_file.o -o mygame -lncurses

main.o: main.cpp
	g++ -c main.cpp

snake.o: snake_file.cpp
	g++ -c snake_file.cpp

clean:
	rm -rf *.o mygame
