compile:
	cp -vr data build/
	g++ -Wall -std=c++17 -O3 src/*.cpp -o iso -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_gfx
	mv -f iso build/
	
run:
	./build/iso

clean:
	rm ./build/iso
