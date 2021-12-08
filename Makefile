CFLAGS = -std=c++17 -O3 -Wall 
OBJS = main.o simulation.o setup.o analysis.o

all: ${OBJS}
	g++ ${CFLAGS} ${OBJS} -o onco_model
	
analysis.o: ./Simulation/analysis.cpp
	g++ ${CFLAGS} -c ./Simulation/analysis.cpp	

main.o: ./console/main.cpp
	g++ ${CFLAGS} -c ./console/main.cpp

clean:
	rm -f onco_model ${OBJS}
