CXX = g++
CXXFLAGS = -I include -L lib -Dmain=SDL_main

SRC = $(wildcard src/core/*.cpp) \
      $(wildcard src/menu/*.cpp) \
      $(wildcard src/option/*.cpp) \
      $(wildcard src/play/*.cpp) \
      $(wildcard src/play/pieces/pawn/pawn.cpp) \
      $(wildcard src/play/pieces/knight/knight.cpp) \
      $(wildcard src/play/pieces/rook/rook.cpp) \
      $(wildcard src/play/pieces/bishop/bishop.cpp) \
      $(wildcard src/play/pieces/king/king.cpp) \
      $(wildcard src/play/pieces/queen/queen.cpp) \
      $(wildcard src/play/castle/castle.cpp) \
      EchoChess.cpp
EXE = EchoChess.exe

LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

DEBUG_FLAGS = -g -Wall
RELEASE_FLAGS = -O2

all: release

debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(EXE)

release: CXXFLAGS += $(RELEASE_FLAGS)
release: $(EXE)

$(EXE): $(SRC)
	$(CXX) $(SRC) -o $(EXE) $(CXXFLAGS) $(LDFLAGS)

clean:
	del /Q *.o $(EXE)

run: $(EXE)
	./$(EXE)
