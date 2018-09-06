
CC = gcc
CFLAGS = -I. -IC:\Users\ruben\Documents\Programs\SDL2-2.0.8\i686-w64-mingw32\include
LDFLAGS = -LC:\Users\ruben\Documents\Programs\SDL2-2.0.8\i686-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2

all:
	${CC} ${CFLAGS} *.c graphics/*.c -o build/tetris.exe ${LDFLAGS}

run: all
	./build/tetris.exe
	
clean:
	rm build/tetris.exe
