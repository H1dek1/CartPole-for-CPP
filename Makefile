MAKEFILE_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
PROGRAM			 := run
INCDIR       := include
SRCDIR			 := src
OBJDIR       := obj
DATADIR      := data
IMAGEDIR     := image

CXX := g++
#CFLAGS := -Wall -c -O3
INCLUDE := -I$(MAKEFILE_DIR)$(INCDIR)/

$(PROGRAM): main.cpp
	$(CXX) $(CFLAGS) $(INCLUDE) $^ -o $@

.PHONY: clean
clean:
	@rm data/* image/* $(PROGRAM) -rf
