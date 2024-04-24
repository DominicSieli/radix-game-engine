CXX = g++
CXXFLAGS = -w -std=c++20 -Wfatal-errors

IFLAGS = -I.
LDFLAGS = -L.
ILIBS = ""
LDLIBS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

build:
	mkdir -p radix/headers;
	cp -r ./lib ./radix;
	cp ./src/*.h ./radix/headers;
	$(CXX) $(CXXFLAGS) ./src/*.cpp -c $(LDFLAGS) $(LDLIBS);
	ar cr ./radix/lradix ./*.o;
	rm -f ./*.o;

clean:
	rm -f ./*.o;
	rm -rf ./radix;

check:
	cppcheck --quiet --enable=all --force --error-exitcode=1 ./src/*.cpp;
