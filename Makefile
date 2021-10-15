SRC=$(wildcard libs/*.cpp)
FILES=$(wildcard *.cpp) $(wildcard */*.cpp)
CC=clang++
FLAGS=-Wall -std=c++17 -g
LIBS=
EXT=
OUT_NAME=ebe
PATHS=.
MACROS=

all: $(SRC)
	$(CC) $(FLAGS) -I $(PATHS) $(MACROS) -o $(OUT_NAME)$(EXT) $(FILES) $^ $(LIBS)

check:
	echo "Test are not yet implemented"

install:
	echo "Install is not yet implemented, use ./ebe"
