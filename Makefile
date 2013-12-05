###########################################################
# Project 4 Makefile
EXEC := raytrace

SRC  := ./src
INC  := ./inc
CXX  := g++
CC   := g++
LEX  := flex
YACC := bison

STD := -std=c++0x
FLAGS := -Wall -ggdb ${STD} -I${INC}

UNAME := $(shell uname)
ifeq ($(UNAME), Darwin)
CORES := $(shell sysctl hw.logicalcpu | cut -d' ' -f 2)
COMPILE_FLAGS := ${FLAGS} -D__MAC__
LIBS := -framework OpenGL -framework GLUT -lpthread -lpng
else
CORES := $(shell grep -c processor /proc/cpuinfo)
COMPILE_FLAGS := ${FLAGS}
LIBS := -lglut -lGLU -lGL -lpthread -lm -lpng
endif

LINKFLAGS := -Wall
CPPFLAGS := ${COMPILE_FLAGS} -DMAX_THREADS=${CORES}
CFLAGS := ${CPPFLAGS}

#INCLUDE = -I/usr/include
#LIBDIR = -L/usr/lib/x86_64-linux-gnu
# Libraries that use native graphics hardware --
#LIBS = -lglut -lGLU -lGL -lpthread -lm
#LIBS = -lglut -lMesaGLU -lMesaGL

OBJECTS = $(patsubst %.cpp, %.o, $(wildcard ${SRC}/*.cpp))
LEXERS = $(patsubst %.lex, %.lex.c, $(wildcard ${SRC}/*.lex))
PARSERS = $(patsubst %.y, %.tab.c, $(wildcard ${SRC}/*.y))
PARSER_HEADERS = $(patsubst %.c, %.h, ${PARSERS})
OBJECTS += $(patsubst %.c, %.o, ${LEXERS})
OBJECTS += $(patsubst %.c, %.o, ${PARSERS})

.PHONEY: all fresh clean run lines

all: ${EXEC}

fresh: clean all

clean:
	rm -f ${SRC}/*.o ${EXEC} ${PARSERS} ${PARSER_HEADERS} ${LEXERS}

run: ${EXEC}
	./${EXEC}

lines:
	@wc -l ${SRC}/*.cpp ${SRC}/*.l ${SRC}/*.y ${INC}/*.hpp

${EXEC}: ${PARSERS} ${LEXERS} ${OBJECTS}
	${CXX} ${LINKFLAGS} -o ${EXEC} ${OBJECTS} ${LIBS}

%.tab.c: %.y
	${YACC} -o $@ ${YACCFLAGS} $<

%.lex.c: %.lex
	${LEX} -o $@ ${LEXFLAGS} $<
