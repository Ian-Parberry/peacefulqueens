SRC = backtrack.cpp svg.cpp
EXE = backtrack

all: $(SRC) $(EXE)

$(EXE): $(SRC)
	g++ -O3 -ffast-math -o $(EXE) $(SRC)

cleanup: 
	rm -f  $(EXE) 
