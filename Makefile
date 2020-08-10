CC=g++
CC_FLAGS=-std=c++17 -O2 -Wall
PYTHON3=python3

test: test.cpp
	$(CC) $(CC_FLAGS) $(^) -o test

p1: p1.cpp
	$(CC) $(CC_FLAGS) $(^) -o p1_test

p2: p2.cpp
	$(CC) $(CC_FLAGS) $(^) -o p2_test

p3: p3.cpp
	$(CC) $(CC_FLAGS) $(^) -o p3_test

p4: p4.cpp
	$(CC) $(CC_FLAGS) $(^) -o p4_test

p5: p5.cpp
	$(CC) $(CC_FLAGS) $(^) -o p5_test

p6: p6.cpp
	$(CC) $(CC_FLAGS) $(^) -o p6_test

p7: p7.cpp
	$(CC) $(CC_FLAGS) $(^) -o p7_test

p8: p8.cpp
	$(CC) $(CC_FLAGS) $(^) -o p8_test

p9: p9.cpp
	$(CC) $(CC_FLAGS) $(^) -o p9_test

p10: p10.cpp
	$(CC) $(CC_FLAGS) $(^) -o p10_test

p11: p11.cpp
	$(CC) $(CC_FLAGS) $(^) -o p11_test

p12: p12.cpp
	$(CC) $(CC_FLAGS) $(^) -o p12_test

p13: p13.cpp
	$(CC) $(CC_FLAGS) $(^) -o p13_test

p14: p14.cpp
	$(CC) $(CC_FLAGS) $(^) -o p14_test

p15: p15.cpp
	$(CC) $(CC_FLAGS) $(^) -o p15_test

p16: p16.py
	$(PYTHON3) $(^)

p17: p17.cpp
	$(CC) $(CC_FLAGS) $(^) -o p17_test

p18: p18.cpp
	$(CC) $(CC_FLAGS) $(^) -o p18_test

p19: p19.py
	$(PYTHON3) $(^)

p20: p20.py
	$(PYTHON3) $(^)

p21: p21.cpp
	$(CC) $(CC_FLAGS) $(^) -o p21_test

p22: p22.cpp
	$(CC) $(CC_FLAGS) $(^) -o p22_test

p23: p23.cpp
	$(CC) $(CC_FLAGS) $(^) -o p23_test

p24: p24.cpp
	$(CC) $(CC_FLAGS) $(^) -o p24_test

p25: p25.py
	$(PYTHON3) $(^)

p26: p26.cpp
	$(CC) $(CC_FLAGS) $(^) -o p26_test

clean:
	rm -f p*_test
	clear
	clear
