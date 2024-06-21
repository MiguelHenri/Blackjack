all: server client

server: server.o dealer.o
	g++ -o server server.o dealer.o

server.o: server.cpp config.h dealer.h
	g++ -c server.cpp

dealer.o: dealer.cpp dealer.h
	g++ -c dealer.cpp

client: client.o
	g++ -o client client.o

client.o: client.cpp config.h
	g++ -c client.cpp

clean:
	rm -f *.o server client