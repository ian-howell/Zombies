HEADERS = $(wildcard src/include/*.h)
INCLUDE = -Isrc/include

CXXSOURCES = $(wildcard src/*.cpp)
CSOURCES = $(wildcard src/*.c)

CXXOBJECTS = $(CXXSOURCES:src/%.cpp=build/%.o)
COBJECTS = $(CSOURCES:src/%.c=build/%.o)

OUTDIR = build
EXECUTABLE = zombies

LINKER = `allegro-config --libs` -lm -ludev

C_FLAGS = -Wall --pedantic-errors -O2

CPP = g++
CC = gcc

default: $(OUTDIR) $(EXECUTABLE)

$(EXECUTABLE): ${CXXOBJECTS} ${COBJECTS} ${HEADERS}
	${CPP} ${C_FLAGS} ${CXXOBJECTS} ${COBJECTS} ${LINKER} -o $@

$(OUTDIR):
	mkdir -p build

${CXXOBJECTS}: build/%.o : src/%.cpp
	-@echo ${CPP} -c $< -o $@ $(INCLUDE)
	${CPP} $(INCLUDE) -c $< -o $@

${COBJECTS}: build/%.o : src/%.c
	${CC} $(INCLUDE) -c $< -o $< -o $@

.PHONY: clean debug

debug: C_FLAGS = -g -Wall --pedantic-errors
debug: $(EXECUTABLE)

clean:
	-@rm -rf $(OUTDIR)
	-@rm -f $(EXECUTABLE)
