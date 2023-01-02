EXEC_NAME :=
ifeq ($(OS),Windows_NT)
	EXEC_NAME = result.exe
else
	EXEC_NAME = result
endif

all:
	@g++ -std=c++20 -O2 test.cpp -o $(EXEC_NAME)

log:
	@g++ -std=c++20 -DLOG_FLAG -O2 test.cpp -o $(EXEC_NAME)

run:
	@./$(EXEC_NAME)


# test: all
# TODO : current all rule change to test, all rule can read from terminal