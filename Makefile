CC=g++
CC_FLAGS=-std=c++17 -O2 -Wall
PYTHON3=python3

p50: p50.cpp
	$(CC) $(CC_FLAGS) -pthread $(^) -o $(@)_test

p88: p88.cpp
	$(CC) $(CC_FLAGS) -pthread $(^) -o $(@)_test

%: %.py
	$(PYTHON3) $(^)

%: %.cpp
	$(CC) $(CC_FLAGS) $(^) -o $(@)_test

clean:
	rm -f p*_test
	clear
	clear
