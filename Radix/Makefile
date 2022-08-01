CXX = g++
IFLAGS = -I.
LDFLAGS = -L.
STATIC_FLAGS = ar rcs
CXXFLAGS = -std=c++20 -Wfatal-errors -w
LDLIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

build:
	mkdir -p ./bin;
	mkdir -p ./obj;
	mkdir -p ../Game/lib;

	#$(CXX) $(CXXFLAGS) ./src/*.cpp -o ./bin/Radix $(IFLAGS) $(LDFLAGS) $(LDLIBS);

	$(CXX) -E -P $(CXXFLAGS) ./src/Radix.h -o ./bin/Radix.h;

	$(CXX) -c $(CXXFLAGS) ./src/*.cpp -static $(IFLAGS) $(LDFLAGS) $(LDLIBS);

	mv ./*.o ./obj;

	$(STATIC_FLAGS) ./bin/libRadix.a ./obj/*.o;

	cp ./bin/libRadix.a ../Game/lib/libRadix.a;
	cp ./bin/Radix.h ../Game/lib/Radix.h;

clean:
	rm -f -r ./bin;
	rm -f -r ./obj;
	rm -f -r ../Game/lib;