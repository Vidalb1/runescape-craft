CXX = g++
CXXFLAGS = -Wall
OBJECTS = Game.o Area.o Hero.o Item.o

proj: $(OBJECTS) proj.cpp
	$(CXX) $(CXXFLAGS) $(OBJECTS) proj.cpp -o proj

Game.o: Game.h Game.cpp Map.o Node.o Hero.o Area.o Item.o
	$(CXX) $(CXXFLAGS) -c Game.cpp

Area.o: Area.h Area.cpp
	$(CXX) $(CXXFLAGS) -c Area.cpp

Map.o: Node.o Map.cpp
	$(CXX) $(CXXFLAGS) -c Map.cpp

Node.o: Node.cpp
	$(CXX) $(CXXFLAGS) -c Node.cpp

Item.o: Item.h Item.cpp
	$(CXX) $(CXXFLAGS) -c Item.cpp

Hero.o: Hero.h Hero.cpp Node.o Map.o
	$(CXX) $(CXXFLAGS) -c Hero.cpp

clean:
	rm *.o
	rm *~

run1:
	./proj proj_map1.txt proj_craft.txt

val1:
	valgrind ./proj proj_map1.txt proj_craft.txt
