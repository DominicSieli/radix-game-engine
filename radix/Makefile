CXX = g++
BIN = -o ./bin/radix
SOURCE = ./src/*.cpp
CXXFLAGS = -w -std=c++20 -Wfatal-errors

IFLAGS = -I
LDFLAGS = -L
ILIBS = "./lib/lua"
LDLIBS = "./lib/lua" -llua -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

build:
	mkdir -p bin

	$(CXX) $(CXXFLAGS) $(SOURCE) $(BIN) $(IFLAGS) $(ILIBS) $(LDFLAGS) $(LDLIBS);

run:
	./bin/radix;

clean:
	rm -rf ./bin;
