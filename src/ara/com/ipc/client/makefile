CC = g++
#CFLAG = -g -Wall
CFLAG = -g 

default: client 

client:  Client.o  ClientMain.o
	$(CC) $(CFLAG) -o client  Client.o ClientMain.o


Server.o: Client.cpp Client.h
	$(CC) $(CFLAG) -c Client.cpp

ServerMain.o: ClientMain.cpp
	$(CC) $(CFLAG) -c ClientMain.cpp

clean:
	$(RM) Client *.o
