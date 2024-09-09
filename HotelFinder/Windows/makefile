REKAS= g++
REKASFLAGS= -Wall

all:run

run: main.o hashtable.o hotel.o
	$(REKAS) $(REKASFLAGS) main.o hashtable.o hotel.o -o run

main.o: main.cpp 
	$(REKAS) $(REKASFLAGS) -c main.cpp -o main.o

hashtable.o: hashtable.cpp hashtable.hpp bst.hpp 
	$(REKAS) $(REKASFLAGS) -c hashtable.cpp -o hashtable.o

hotel.o: hotel.cpp hotel.hpp
	$(REKAS) $(REKASFLAGS) -c hotel.cpp -o hotel.o

clean:
	del -f *.o *.exe run
