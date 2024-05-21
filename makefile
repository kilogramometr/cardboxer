LINKS := -lsfml-graphics -lsfml-window -lsfml-system
BINS := ./main.cpp $(wildcard ./sources/*.cpp)
OBJS := $(wildcard ./*.o)

make:
	g++ -c ${BINS}
	g++ -std=c++14 -o ./build/app ${OBJS} ${LINKS}

run:
	./build/app

clean:
	rm -rvf *.o