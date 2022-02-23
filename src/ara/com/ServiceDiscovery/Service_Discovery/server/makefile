CC = g++
#CFLAG = -g -Wall
CFLAG = -g 

default: server

server:  CServer.o  ServerMain.o
	$(CC) $(CFLAG) -o server  CServer.o ServerMain.o



CServer.o: CServer.cpp CServer.h
	$(CC) $(CFLAG) -c CServer.cpp

ServerMain.o: ServerMain.cpp
	$(CC) $(CFLAG) -c ServerMain.cpp

clean:
	$(RM) server *.o
