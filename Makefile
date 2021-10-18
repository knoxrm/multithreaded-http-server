cc=g++

all: server

server: server.cpp server.o
	${cc} -Wall server.cpp -o server.o -lpthread

client: client.cpp
	$(cc) -Wall client.cpp -o client.o 

clean:
	rm server.o client.o
