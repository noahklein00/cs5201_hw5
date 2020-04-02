###############################################################################
## -->Makefile<--
###############################################################################
##
## Programmer : Noah Klein
## Instructor : Price
## Class      : CS5201 Spring 2020
## Assignment : Homework 5 - Matrices, Filters, and Guidance
## Filename   : Makefile
##
###############################################################################

###############################################################################
#This makefile will build an executable for the 2020-sp-a-hw5-nekgr8 directory.
###############################################################################

CXX = /usr/bin/g++
FLAGS = -Wall -Wextra -Wpedantic -Werror
OBJECTS = driver.o\
          PID.o

.SUFFIXES: .cpp

.cpp.o: $<
	${CXX} -c ${FLAGS} $< -o $@

default: all

all: hw5.out

hw5.out: ${OBJECTS}
	${CXX} ${FLAGS} ${OBJECTS} -o $@

clean:
	-@rm -f core > /dev/null 2>&1
	-@rm -f hw5.out > /dev/null 2>&1
	-@rm -f ${OBJECTS} > /dev/null 2>&1

# Dependency lists for the various source files
driver.o: driver.cpp\
          nTrix.h\
          nTrix.hpp\
          nVect.h\
          nVect.hpp\
          PID.h\
          PID.cpp\
          lander.h\
          lander.hpp\
          filter.h\
          dummy.h\
          dummy.hpp\
          lowPass.h\
          lowPass.hpp\
          kalman.h\
          kalman.hpp
	g++ -c driver.cpp

PID.o: PID.cpp\
       nVect.h\
       nVect.hpp\
       PID.h
	g++ -c PID.cpp
