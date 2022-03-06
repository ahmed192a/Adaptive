CC = g++
#CFLAG = -g -Wall
CFLAG = -g 

default: client 

client:  CClient.o  ClientMain.o
	$(CC) $(CFLAG) -o client  CClient.o ClientMain.o


CServer.o: CClient.cpp CClient.h
	$(CC) $(CFLAG) -c CClient.cpp

ServerMain.o: ClientMain.cpp
	$(CC) $(CFLAG) -c ClientMain.cpp

clean:
	$(RM) Client *.o
