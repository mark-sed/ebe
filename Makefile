SRC=$(wildcard libs/*.c)
FILES=$(wildcard *.cpp)
CC=g++
FLAGS=-Wall -std=c++17 -g
LIBS=
EXT=
OUT_NAME=ebe
PATHS=libs

all: $(SRC)
	$(CC) $(FLAGS) -I $(PATHS) -o $(OUT_NAME)$(EXT) $(FILES) $^ $(LIBS)

check:
	echo "Test are not yet implemented"

install:
	echo "Install is not yet implemented, use ./ebe"
