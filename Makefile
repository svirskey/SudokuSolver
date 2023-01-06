# all: 
# 	mkdir -p build
# 	cd build && cmake -G "Unix Makefiles" ..
# 	cd build && cmake --build . 
MKDIR_COMMAND :=
ifeq ($(OS),Windows_NT)
	MKDIR_COMMAND += if not exist ./build mkdir build
else
	MKDIR_COMMAND += mkdir -p build
endif

all: test

test: run_test

build_test:
	echo $(shell gcc -dumpmachine)
	$(MKDIR_COMMAND)
	cmake -S . -B build
	cmake --build build

run_test: build_test
	cd build && ctest

#main:
#	g++ -std=c++20 main.cpp && ./a.out

clean:
	rm -rf ./build
	rm -f a.out
	rm -f *.o
	rm -f output.txt

# test: all
# TODO : current all rule change to test, all rule can read from terminal