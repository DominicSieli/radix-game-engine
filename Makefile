CXX = g++
OUTPUT = -o
SOURCE = ./src/*.cpp
BINARY = ./game/radix
CXXFLAGS = -w -std=c++20 -Wfatal-errors

IFLAGS = -I.
LDFLAGS = -L.
ILIBS = ""
LDLIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

build:
	$(CXX) $(CXXFLAGS) $(SOURCE) $(OUTPUT) $(BINARY) $(LDFLAGS) $(LDLIBS);

clean:
	rm -f $(BINARY);

check:
	cppcheck --quiet --enable=all --force --error-exitcode=1 $(SOURCE);
