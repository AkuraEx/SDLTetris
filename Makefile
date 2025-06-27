compile: flip run

run:
	./out/tetris.exe

flip:
	g++ ./src/tetris.cpp ./src/entity.cpp ./src/texture.cpp ./src/score.cpp -o ./out/tetris.exe -lSDL3 -lSDL3_image