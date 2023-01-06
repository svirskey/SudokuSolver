# all: 
# 	mkdir -p build
# 	cd build && cmake -G "Unix Makefiles" ..
# 	cd build && cmake --build . 
OSFLAG 				:=
ifeq ($(OS),Windows_NT)
	OSFLAG += -G 'Visual Studio 17 2022'
else
	OSFLAG += -G 'Unix Makefiles'
endif

all: test

test: run_test

build_test:
	mkdir -p build
	cmake ${OSFLAG} -S . -B build
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