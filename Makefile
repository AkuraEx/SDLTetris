compile: flip run

run:
	./out/tetris.exe

flip:
	g++ ./src/tetris.cpp ./src/entity.cpp -o ./out/tetris.exe -lSDL3 -lSDL3_image