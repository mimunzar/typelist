CXXFLAGS=-std=c++11 -g -Wall -Wextra -Wpedantic -Wconversion -Wstrict-aliasing \
	-Wreorder -Warray-bounds -Wuseless-cast -Wshadow -Wmaybe-uninitialized

all: main

clean:
	@rm -vf main

rebuild: clean all

