CC=g++
CC_FLAGS=-std=c++17 -O2 -Wall
PYTHON3=python3

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

p27: p27.cpp
	$(CC) $(CC_FLAGS) $(^) -o p27_test

p28: p28.cpp
	$(CC) $(CC_FLAGS) $(^) -o p28_test

p29: p29.py
	$(PYTHON3) $(^)

p30: p30.cpp
	$(CC) $(CC_FLAGS) $(^) -o p30_test

p31: p31.cpp
	$(CC) $(CC_FLAGS) $(^) -o p31_test

p35: p35.cpp
	$(CC) $(CC_FLAGS) $(^) -o p35_test

p36: p36.py
	$(PYTHON3) $(^)

p37: p37.cpp
	$(CC) $(CC_FLAGS) $(^) -o p37_test

p38: p38.cpp
	$(CC) $(CC_FLAGS) $(^) -o p38_test

p39: p39.cpp
	$(CC) $(CC_FLAGS) $(^) -o p39_test

p40: p40.cpp
	$(CC) $(CC_FLAGS) $(^) -o p40_test

p41: p41.cpp
	$(CC) $(CC_FLAGS) $(^) -o p41_test

p42: p42.cpp
	$(CC) $(CC_FLAGS) $(^) -o p42_test

p43: p43.cpp
	$(CC) $(CC_FLAGS) $(^) -o p43_test

p44: p44.cpp
	$(CC) $(CC_FLAGS) $(^) -o p44_test

p45: p45.cpp
	$(CC) $(CC_FLAGS) $(^) -o p45_test

p46: p46.cpp
	$(CC) $(CC_FLAGS) $(^) -o p46_test

p47: p47.cpp
	$(CC) $(CC_FLAGS) $(^) -o p47_test

p48: p48.py
	$(PYTHON3) $(^)

p50: p50.cpp
	$(CC) $(CC_FLAGS) -pthread $(^) -o p50_test

p52: p52.cpp
	$(CC) $(CC_FLAGS) $(^) -o p52_test

p53: p53.cpp
	$(CC) $(CC_FLAGS) $(^) -o p53_test

p55: p55.cpp
	$(CC) $(CC_FLAGS) $(^) -o p55_test

p58: p58.cpp
	$(CC) $(CC_FLAGS) $(^) -o p58_test

p59: p59.cpp
	$(CC) $(CC_FLAGS) $(^) -o p59_test

p62: p62.cpp
	$(CC) $(CC_FLAGS) $(^) -o p62_test

p63: p63.py
	$(PYTHON3) $(^)

p67: p67.cpp
	$(CC) $(CC_FLAGS) $(^) -o p67_test

p78: p78.py
	$(PYTHON3) $(^)

p81: p81.cpp
	$(CC) $(CC_FLAGS) $(^) -o p81_test

p82: p82.cpp
	$(CC) $(CC_FLAGS) $(^) -o p82_test

p83: p83.cpp
	$(CC) $(CC_FLAGS) $(^) -o p83_test

clean:
	rm -f p*_test
	clear
	clear
