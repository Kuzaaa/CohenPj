COMPONENTS = Graph.cpp suffix_hash_map.cpp

all: a.out clean

a.out: main.cpp $(COMPONENTS)
	g++ -std=c++17 main.cpp $(COMPONENTS) -Wall -o main

clean:
	rm -rf *.o
