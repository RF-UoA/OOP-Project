play: main.o gameObject.o tower.o enemy.o gameMap.o tile.o
	g++ main.o -lsfml-system -lsfml-window -lsfml-graphics gameObject.o tower.o enemy.o tile.o gameMap.o -o play

main.o: main.cpp
	g++ -c main.cpp 

gameObject.o: gameObject.cpp
	g++ -c gameObject.cpp

tower.o: tower.cpp
	g++ -c tower.cpp

enemy.o: enemy.cpp
	g++ -c enemy.cpp

tile.o: tile.cpp
	g++ -c tile.cpp

gamegameMap.o: gameMap.cpp
	g++ -c gameMap.cpp

# classname.o: classname.cpp classname.h
#	g++ -c classname.cpp

clean:
	rm play
	rm *.o

# use 'make' in terminal to run file
# use 'make clean' in ternminal to remove executable
# Under above comment block, add class dependencies when new classes are created
# Under 'play' include class.o dependencies to compiler command
