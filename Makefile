play: main.o gameObject.o tower.o AOETower.o rangedTower.o enemy.o gameMap.o
	g++ main.o -lsfml-system -lsfml-window -lsfml-graphics gameObject.o tower.o AOETower.o rangedTower.o enemy.o gameMap.o -o play

main.o: main.cpp
	g++ -c main.cpp 

gameObject.o: gameObject.cpp
	g++ -c gameObject.cpp

tower.o: tower.cpp
	g++ -c tower.cpp

AOETower.o: AOETower.cpp
	g++ -c AOETower.cpp

rangedTower.o: rangedTower.cpp
	g++ -c rangedTower.cpp

enemy.o: enemy.cpp
	g++ -c enemy.cpp

gamegameMap.o: gameMap.cpp
	g++ -c gameMap.cpp

enemy_light.o: enemy_light.cpp
	g++ -c enemy_light.cpp

enemy_medium.o: enemy_medium.cpp
	g++ -c enemy_medium.cpp

# classname.o: classname.cpp classname.h
#	g++ -c classname.cpp

clean:
	rm play
	rm *.o

# use 'make' in terminal to run file
# use 'make clean' in ternminal to remove executable
# Under above comment block, add class dependencies when new classes are created
# Under 'play' include class.o dependencies to compiler command
