LINKS := -lsfml-graphics -lsfml-window -lsfml-system -ljsoncpp
BINS := ./main.cpp $(wildcard ./sources/*.cpp)
OBJS := $(wildcard ./*.o)

make: # you may need to make twice if main.o doesn't exist. I do not understand why this error happens
	mkdir -p build
	g++ -c ${BINS}
	g++ -std=c++14 -o ./build/app ${OBJS} ${LINKS}
	cp -ru ./cards ./build/
	cp -ru ./res ./build/
	cp -ru ./enemies ./build/

update:
	cp -ru ./cards ./build/
	cp -ru ./res ./build/
	cp -ru ./enemies ./build/

run:
	cd build; \
	./app

rebuild:
	make
	make run

clean:
	rm -rvf *.o
