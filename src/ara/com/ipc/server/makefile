CC = g++
#CFLAG = -g -Wall
CFLAG = -g 

default: server

server:  Server.o  ServerMain.o
	$(CC) $(CFLAG) -o server  Server.o ServerMain.o



Server.o: Server.cpp Server.h
	$(CC) $(CFLAG) -c Server.cpp

ServerMain.o: ServerMain.cpp
	$(CC) $(CFLAG) -c ServerMain.cpp

clean:
	$(RM) server *.o
