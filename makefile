CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET = monopoly
OBJS = main.o Game.o Board.o Player.o Dice.o Property.o GUI.o
SOURCES = main.cpp Game.cpp Board.cpp Player.cpp Dice.cpp Property.cpp GUI.cpp

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

gui:
	g++ -c testGUI.cpp
	g++ testGUI.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
	
test: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test
TestCounter.o:
	$(CXX) $(CXXFLAGS) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system
Test.o:
	$(CXX) $(CXXFLAGS) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm -f $(TARGET) $(OBJS)
