server: server.o config.h
	g++ -o server server.o

server.o: server.cpp config.h
	g++ -c server.cpp

client: client.o config.h
	g++ -o client client.o

client.o: client.cpp config.h
	g++ -c client.cpp

clean:
	rm *.o
	clear