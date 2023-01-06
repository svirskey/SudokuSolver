all: 
	mkdir -p build
	cd build
	cmake -G "MinGW Makefiles" ..
	

# test: all
# TODO : current all rule change to test, all rule can read from terminal