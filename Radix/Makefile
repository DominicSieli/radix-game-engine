debug:
	mkdir -p bin/debug;
	mkdir -p ../Game/lib/debug;
	g++ -w -std=c++14 -Wfatal-errors \
	./src/*.cpp \
	-o bin/debug/radix \
	-I"./lib/glm" \
	-L"./lib/glm" \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer;
	cp bin/debug/radix ../Game/lib/debug;

master:
	mkdir -p bin/master;
	mkdir -p ../Game/lib/master;
	g++ -w -std=c++14 -Wfatal-errors \
	./src/*.cpp \
	-o bin/master/radix \
	-I"./lib/glm" \
	-L"./lib/glm" \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer;
	cp bin/master/radix ../Game/lib/master;

clean:
	rm -f -r ./bin;
	rm -f -r ../Game/lib;

run-debug:
	./bin/debug/radix;

run-master:
	./bin/master/radix;