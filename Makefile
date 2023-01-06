
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

clean:
	rm -rf ./build
	rm -f a.out
	rm -f *.o
	rm -f output.txt

# TODO : all rule which will read from terminal or make a lib