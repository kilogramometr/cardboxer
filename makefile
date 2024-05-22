LINKS := -lsfml-graphics -lsfml-window -lsfml-system
BINS := ./main.cpp $(wildcard ./sources/*.cpp)
OBJS := $(wildcard ./*.o)

make:
	g++ -c ${BINS}
	g++ -std=c++14 -o ./build/app ${OBJS} ${LINKS}
	cp -ru ./cards ./build/
	cp -ru ./res ./build/

run:
	./build/app

clean:
	rm -rvf *.o