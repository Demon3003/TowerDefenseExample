map.o:
	g++ -c map.cpp -I /Library/Developer/usr/include

cache.o:
	g++ -c cache.cpp -I /Library/Developer/usr/include

drawEnemy.o:
	g++ -std=c++14 -c Enemy.cpp -I /Library/Developer/usr/include

Tower.o:
	g++ -std=c++14 -c Tower.cpp -I /Library/Developer/usr/include
 
main.o:
	g++ -c main.cpp -I /Library/Developer/usr/include
	
all: 
	g++ map.o cache.o Enemy.o Tower.o main.o -L /Library/Developer/usr/lib -lsfml-graphics -lsfml-window -lsfml-system -o myProg

run:
	export LD_LIBRARY_PATH=/Library/Developer/usr/lib && ./myProg

clear:
	rm *.o myProg