Battleship: main.o Executive.o Players.o AI.o Trackers.o Boards.o Utils.o
	g++ -std=c++11 -g -Wall main.o Executive.o Players.o AI.o Trackers.o Boards.o Utils.o -o Battleship

main.o: main.cpp Executive.h
	g++ -std=c++11 -g -Wall -c  main.cpp

Executive.o: Executive.h Executive.cpp AI.h
	g++ -std=c++11 -g -Wall -c  Executive.cpp

AI.o: AI.h AI.cpp Players.h
	g++ -std=c++11 -g -Wall -c  AI.cpp

Players.o: Players.h Players.cpp Boards.h Trackers.h
	g++ -std=c++11 -g -Wall -c  Players.cpp

Trackers.o: Trackers.h Trackers.cpp Utils.h
	g++ -std=c++11 -g -Wall -c  Trackers.cpp

Boards.o: Boards.h Boards.cpp
	g++ -std=c++11 -g -Wall -c  Boards.cpp

Utils.o: Utils.h Utils.cpp
	g++ -std=c++11 -g -Wall -c  Utils.cpp

clean:
	rm *.o *.gch Battleship
