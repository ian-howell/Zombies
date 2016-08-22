HEADERS = $(wildcard *.h)
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:%.cpp=%.o)
LINKER = allegro-config --libs
C_FLAGS = -Wall --pedantic-errors -O2

CPP = g++

game: ${OBJECTS} ${HEADERS}
	${CPP} ${C_FLAGS} ${OBJECTS} `allegro-config --libs` -o game

%.o: %.cpp ${HEADERS}
	${CPP} -c $<

.PHONY: clean debug

debug: C_FLAGS = -g -Wall --pedantic-errors
debug: game

clean:
	-@rm -f *.o
	-@rm -f game
