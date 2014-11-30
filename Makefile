all:projet projet2

projet:try.o
	g++ try.o -o projet -lserial -lstdc++

projet2:main.o
	g++ main.o -o projet -lserial -lstdc++

main.o:main.cpp
	g++ -g -c -Wall main.cpp
	
try.o:try.cpp
	g++ -g -c -Wall try.cpp

clean:
	rm -f *.o

vclean: clean
	rm -f projet

vvclean: all clean
