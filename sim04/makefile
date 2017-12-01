CFLAGS = -std=c++11

main: config_data.o meta_data.o node.o timer.o output_log.o
		g++ -c main.cpp
		g++ main.o config_data.o meta_data.o node.o timer.o output_log.o -o sim04 -std=c++11 -lpthread

config_data.o: config_data.cpp config_data.h meta_data.h node.h timer.h output_log.h
		g++ -c config_data.h
		g++ -c config_data.cpp -std=c++11

meta_data.o: meta_data.cpp meta_data.h node.h timer.h
		g++ -c meta_data.h
		g++ -c meta_data.cpp

node.o: node.cpp node.h timer.h
		g++ -c node.h
		g++ -c node.cpp

timer.o: timer.cpp timer.h
		g++ -c timer.h
		g++ -c timer.cpp

output_log.o: output_log.cpp output_log.h
		g++ -c output_log.h
		g++ -c output_log.cpp

clean:
	rm *.o sim03
