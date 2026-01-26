TARGET 		:= complex
CC 			:= clang++
OUTPUT 		:= complex.o
INPUT 		:= complex.c
INCLUDE 	:= include
LIB 		:= -lgtest
BUILDDIR    := ./bin

$(TARGET): $(OUTPUT)
	$(CC) $(OUTPUT) -I $(INCLUDE) -o $(TARGET)

$(OUTPUT): $(INPUT) $(INCLUDE)
	$(CC) -c $(INPUT) -I $(INCLUDE) -o $(OUTPUT)

# *********** TEST ***********
TEST_TARGET = unitTest
TEST_OUTPUT = unit_test.o
TESTMAIN_OUTPUT = utest_main.o
TEST = unit_test.c
TESTMAIN = utest_main.c

$(TEST_TARGET): $(TEST_OUTPUT) $(TESTMAIN_OUTPUT) $(OUTPUT)
	$(CC) $(TEST_OUTPUT) $(TESTMAIN_OUTPUT) $(OUTPUT) -I $(INCLUDE) $(LIB) -o $(TEST_TARGET)

$(TESTMAIN_OUTPUT): $(TEST) $(TESTMAIN)
	$(CC) -c $(TESTMAIN) -I $(INCLUDE) -o $(TESTMAIN_OUTPUT)

$(TEST_OUTPUT): $(TEST) $(TESTMAIN)
	$(CC) -c $(TEST) -I $(INCLUDE) -o $(TEST_OUTPUT)

clean:
	@$(RM) -rf *.o
