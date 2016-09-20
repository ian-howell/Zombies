HEADERS = $(wildcard *.h)
CXXSOURCES = $(wildcard *.cpp)
CSOURCES = $(wildcard *.c)
CXXOBJECTS = $(CXXSOURCES:%.cpp=%.o)
COBJECTS = $(CSOURCES:%.c=%.o)
LINKER = `allegro-config --libs` -lm -ludev
C_FLAGS = -Wall --pedantic-errors -O2

CPP = g++
CC = gcc

game: ${CXXOBJECTS} ${COBJECTS} ${HEADERS}
	${CPP} ${C_FLAGS} ${CXXOBJECTS} ${COBJECTS} ${LINKER} -o game

${CXXOBJECTS}: %.o : %.cpp
	${CPP} -c $<

${COBJECTS}: %.o : %.c
	${CC} -c $<

.PHONY: clean debug

debug: C_FLAGS = -g -Wall --pedantic-errors
debug: game

clean:
	-@rm -f *.o
	-@rm -f game
