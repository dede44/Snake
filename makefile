screen.x:  screen.o getChar.o gameBoard.o worm.o
	g++ -ggdb -o screen.x screen.o getChar.o gameBoard.o worm.o -lcurses -ltermcap

screen.o: screen.cpp 
	g++ -c -ggdb screen.cpp -o screen.o

gameBoard.o: gameBoard.cpp gameBoard.hpp
	g++ -c -ggdb gameBoard.cpp -o gameBoard.o

getChar.o: getChar.cpp 
	gcc -c -ggdb getChar.cpp -o getChar.o

worm.o: worm.cpp worm.hpp
	g++ -c -ggdb worm.cpp -o worm.o

clean:
	/bin/rm -f screen.x screen.o getChar.o *~ 
