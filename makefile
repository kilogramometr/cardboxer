LINKS := -lsfml-graphics -lsfml-window -lsfml-system
BINS := ./main.cpp $(wildcard ./sources/*.cpp)
OBJS := $(wildcard ./*.o)

make: # you may need to make twice if main.o doesn't exist. I do not understand why this error happens
	g++ -c ${BINS}
	g++ -std=c++14 -o ./build/app ${OBJS} ${LINKS}
	cp -ru ./cards ./build/
	cp -ru ./res ./build/

run:
	./build/app

clean:
	rm -rvf *.o
