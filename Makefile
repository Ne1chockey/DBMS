main: main.o Engine.o Parser.o App.o
	g++ -o main main.o Engine.o Parser.o App.o

main.o: main.cpp Engine.h Parser.h App.h
	g++ -c main.cpp

Engine.o: Engine.h
	g++ -c Engine.cpp

Parser.o: Parser.h
	g++ -c Parser.cpp

App.o: App.h
	g++ -c App.cpp

clean:
	rm-rf *.o
