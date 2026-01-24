TARGET = bin/complex
CC = clang
OUTPUT = complex.o
INPUT = complex.c
INCLUDE = complex.h

# For Testing
TEST_TARGET = bin/complexTest
TEST = test/unit_test.c
TESTMAIN = test/utest_main.c

$(TARGET): $(OUTPUT)
	$(CC) $(OUTPUT) -I $(INCLUDE) -o $(TARGET)

$(OUTPUT): $(INPUT) $(INCLUDE)
	$(CC) -c $(INPUT)

test: $()

clean:
	rm *.o
