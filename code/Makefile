all: server client

server: server.o dealer.o blackjack.o config.o
	g++ -o server server.o dealer.o blackjack.o config.o

server.o: server.cpp config.h dealer.h blackjack.h
	g++ -c server.cpp

dealer.o: dealer.cpp dealer.h
	g++ -c dealer.cpp

blackjack.o: blackjack.cpp blackjack.h
	g++ -c blackjack.cpp

config.o: config.cpp config.h
	g++ -c config.cpp

client: client.o blackjack.o config.o
	g++ -o client client.o blackjack.o config.o

client.o: client.cpp config.h blackjack.h
	g++ -c client.cpp

clean:
	rm -f *.o server client