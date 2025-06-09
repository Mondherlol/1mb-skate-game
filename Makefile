CC = gcc
CFLAGS = -I./include -L./lib -lraylib -lopengl32 -lgdi32 -lwinmm -Os -s
SRC = src/player.c src/obstacle.c src/game.c main.c
OBJ = $(SRC:.c=.o)
OUT = bin/monjeu.exe

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT) $(CFLAGS)

clean:
	rm -f $(OBJ) $(OUT)
