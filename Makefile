play: main.o
	g++ main.o -lsfml-system -lsfml-window -lsfml-graphics -o play

main.o: main.cpp
	g++ -c main.cpp 

# classname.o: classname.cpp classname.h
#	g++ -c classname.cpp

clean:
	rm play
	rm *.o

# use 'make' in terminal to run file
# use 'make clean' in ternminal to remove executable
# Under above comment block, add class dependencies when new classes are created
# Under 'play' include class.o dependencies to compiler command
