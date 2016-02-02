EXE = BCDIntervalClock
C_FILES = displayBCDClock.c pa2.c parseStartTime.c updateClockDecimal.c usage.c
H_FILES = pa2.h pa2Strings.h
S_FILES = updateClockDecimalValue.s convertToBCD.s checkRange.s isNegative.s printChar.s

TEST_CONVERT_FILES = test.h pa2.h convertToBCD.s testconvertToBCD.c
TEST_CONVERT_EXE = testconvertToBCD
TEST_UPDATE_FILES = test.h pa2.h updateClockDecimalValue.s testupdateClockDecimalValue.c
TEST_UPDATE_EXE = testupdateClockDecimalValue
TEST_PARSE_FILES = test.h pa2.h parseStartTime.c testparseStartTime.c checkRange.s isNegative.s
TEST_PARSE_EXE = testparseStartTime


default: $(C_FILES) $(S_FILES)
	gcc -o $(EXE) $(C_FILES) $(S_FILES)

clean:
	rm -rf $(EXE) $(TEST_CONVERT_EXE) $(TEST_UPDATE_EXE) $(TEST_PARSE_EXE)

testconvertToBCD: $(TEST_CONVERT_FILES)
	@echo "Compiling testconvertToBCD.c"
	gcc -g -o $(TEST_CONVERT_EXE) $(TEST_CONVERT_FILES)
	@echo "Done."

runtestconvertToBCD: $(TEST_CONVERT_EXE)
	@echo "Running testconvertToBCD"
	@./$(TEST_CONVERT_EXE)

testupdateClockDecimalValue: $(TEST_UPDATE_FILES)
	@echo "Compiling testupdateClockDecimalValue.c"
	gcc -g -o $(TEST_UPDATE_EXE) $(TEST_UPDATE_FILES)
	@echo "Done."

runtestupdateClockDecimalValue: $(TEST_UPDATE_EXE)
	@echo "Running testupdateClockDecimalValue"
	@./$(TEST_UPDATE_EXE)

testparseStartTime: $(TEST_PARSE_FILES)
	@echo "Compiling testparseStartTime.c"
	gcc -g -o $(TEST_PARSE_EXE) $(TEST_PARSE_FILES)
	@echo "Done."

runtestparseStartTime: $(TEST_PARSE_EXE)
	@echo "Running testparseStartTime"
	@./$(TEST_PARSE_EXE)
