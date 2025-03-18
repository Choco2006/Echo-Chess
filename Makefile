CXX = g++
CXXFLAGS = -I include -L lib -Dmain=SDL_main

SRC = $(wildcard src/core/*.cpp src/menu/*.cpp) EchoChess.cpp

EXE = EchoChess.exe

LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer

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
