LINKS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-system

make:
	g++ -c main.cpp
	g++ -std=c++14 -o ./build/app ./main.cpp ${LINKS}

run:
	./build/app

clean:
	rm -rvf *.o