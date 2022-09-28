all : main

main : main.o List.o
	g++ -Wall -g -o main main.o List.o
main.o : main.cpp List.h
	g++ -Wall -g -c main.cpp
List.o : List.cpp List.h
	g++ -Wall -g -c List.cpp