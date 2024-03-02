CXX = g++
IFLAGS = -I.
LDFLAGS = -L.
STATIC_FLAGS = ar rcs
CXXFLAGS = -std=c++20 -Wfatal-errors -w
LDLIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

build:
	mkdir -p ./bin;
	mkdir -p ./obj;
	mkdir -p ../game/lib;

	#$(CXX) $(CXXFLAGS) ./src/*.cpp -o ./bin/radix $(IFLAGS) $(LDFLAGS) $(LDLIBS);

	$(CXX) -E -P $(CXXFLAGS) ./src/radix.h -o ./bin/radix.h;

	$(CXX) -c $(CXXFLAGS) ./src/*.cpp -static $(IFLAGS) $(LDFLAGS) $(LDLIBS);

	mv ./*.o ./obj;

	$(STATIC_FLAGS) ./bin/libradix.a ./obj/*.o;

	cp ./bin/libradix.a ../game/lib/libradix.a;
	cp ./bin/radix.h ../game/lib/radix.h;

clean:
	rm -f -r ./bin;
	rm -f -r ./obj;
	rm -f -r ../game/lib;