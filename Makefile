MAKEFILE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
PROGRAM			 := run
INCDIR       := include
SRCDIR			 := src
OBJDIR       := obj
DATADIR      := data
IMAGEDIR     := image

CXX := g++
CFLAGS := -Wall -c -O3

$(PROGRAM): main.cpp
	@$(CXX) $^ -o $@

.PHONY: clean
clean:
	@rm data/* image/* $(PROGRAM)
