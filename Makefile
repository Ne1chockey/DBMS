make all: main commandline

commandline: commandline.o Engine.o Parser.o App.o Table.o
	g++ -std=c++11 -o commandline commandline.o Engine.o Parser.o App.o Table.o

commandline.o: commandline.cpp Engine.h Parser.h App.h Table.h
	g++ -std=c++11 -c commandline.cpp

main: main.o Engine.o Parser.o App.o Table.o
	g++ -std=c++11 -o main main.o Engine.o Parser.o App.o Table.o

main.o: main.cpp Engine.h Parser.h App.h Table.h
	g++ -std=c++11 -c main.cpp

Engine.o: Engine.h
	g++ -std=c++11 -c Engine.cpp

Parser.o: Parser.h
	g++ -std=c++11 -c Parser.cpp

App.o: App.h
	g++ -std=c++11 -c App.cpp

Table.o: Table.h
	g++ -std=c++11 -c Table.cpp

clean:
	rm -rf *.o main
