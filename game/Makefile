CXX = g++
IFLAGS = -I.
LDFLAGS = -L./lib
STATIC_FLAGS = ar rcs
CXXFLAGS = -std=c++20 -Wfatal-errors -w
LDLIBS = -lradix -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

build:
	mkdir -p bin;

	$(CXX) $(CXXFLAGS) ./src/*.cpp -o ./bin/game $(IFLAGS) $(LDFLAGS) $(LDLIBS);

clean:
	rm -f -r ./bin;

run:
	./bin/game;