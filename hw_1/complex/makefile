TARGET 		:= bin/complex
CC 			:= clang++
OUTPUT 		:= bin/complex.o
INPUT 		:= src/complex.c
INCLUDE 	:= include
LIB 		:= -lgtest
BUILDDIR    := ./bin

$(TARGET): $(OUTPUT)
	$(CC) $(OUTPUT) -I $(INCLUDE) -o $(TARGET)

$(OUTPUT): $(INPUT) $(INCLUDE)
	$(CC) -c $(INPUT) -I $(INCLUDE) -o $(OUTPUT)

# *********** TEST ***********
TEST_TARGET = bin/test
TEST_OUTPUT = bin/unit_test.o
TESTMAIN_OUTPUT = bin/utest_main.o
TEST = test/unit_test.c
TESTMAIN = test/utest_main.c

$(TEST_TARGET): $(TEST_OUTPUT) $(TESTMAIN_OUTPUT) $(OUTPUT)
	$(CC) $(TEST_OUTPUT) $(TESTMAIN_OUTPUT) $(OUTPUT) -I $(INCLUDE) $(LIB) -o $(TEST_TARGET)

$(TESTMAIN_OUTPUT): $(TEST) $(TESTMAIN)
	$(CC) -c $(TESTMAIN) -I $(INCLUDE) -o $(TESTMAIN_OUTPUT)

$(TEST_OUTPUT): $(TEST) $(TESTMAIN)
	$(CC) -c $(TEST) -I $(INCLUDE) -o $(TEST_OUTPUT)

clean:
	@$(RM) -rf $(BUILDDIR)/*.o
