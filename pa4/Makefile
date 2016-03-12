# Filename: Makefile
# Description: Makefile for PA4 assignment

TARGET		= myuniq

HEADERS		= pa4.h pa4Strings.h test.h

C_SRCS		= findUniq.c printResults.c\
		  parseInputStream.c sortInputCompare.c usage.c\
		  printErrors.c parseArgs.c runUniq.c setErrorInfo.c\
		  pa4Globals.c pa4gettimeofday.c

ASM_SRCS	= compareCount.s compareLine.s strIgnoreCaseCmp.s pa4.s

C_OBJS		= $(C_SRCS:.c=.o)

ASM_OBJS	= compareCount.o compareLine.o strIgnoreCaseCmp.o pa4.o

OBJS		= ${C_OBJS} ${ASM_OBJS}

TEST_SRCS	= testparseArgs.c testparseInputStream.c teststrIgnoreCaseCmp\
		testfindUniq.c testsortInputCompare.c

TEST_EXE	= $(TEST_SRCS:.c=)

TEST_DIR	= unit_tests

# Define programs used
MAKE = gmake # Needed because default make on ieng9 is not GNU make
GCC		= gcc
ASM		= $(GCC)
LINT		= lint

# Flags used
GCC_FLAGS	= -c -g -Wall -D__EXTENSIONS__ -std=c99
LINT_FLAGS1	= -c -err=warn
LINT_FLAGS2	= -u -err=warn
ASM_FLAGS	= -c -g
LD_FLAGS	= -g -Wall

#
# Standard rules
#
.s.o:
	@echo "Assembling each assembly source file separately ..."
	$(ASM) $(ASM_FLAGS) $<
	@echo ""

.c.o:
	@echo "Linting each C source file separately ..."
	$(LINT) $(LINT_FLAGS1) $<
	@echo ""
	@echo "Compiling each C source file separately ..."
	$(GCC) $(GCC_FLAGS) $<
	@echo ""

#
# Simply have our project target be the executable
#
$(TARGET):	$(OBJS)
	@echo "2nd phase lint on all C source files ..."
	$(LINT) $(LINT_FLAGS2) *.ln
	@echo ""
	@echo "Linking all object modules ..."
	$(GCC) -o $(TARGET) $(LD_FLAGS) $(OBJS)
	@echo ""
	@echo "Done."

${C_OBJS}:      ${HEADERS}

clean:
	@echo "Cleaning up project directory ..."
	/usr/bin/rm -f *.o a.out *.ln core $(TARGET) $(TEST_EXE)
	@echo ""
	@echo "Clean."

new:
	make clean
	make

# --- TESTING ---
setupTest:
	# Move all headers into test directory
	echo ${addsuffix .o, ${basename ${DEPEND}}}
	cp $(HEADERS) $(TEST_DIR)

cleanTest:
	# Remove all header from test directory
	rm $(addprefix $(TEST_DIR)/,$(HEADERS))

LINT_TEST_FLAGS		= -x -u -err=warn

# General purpose compilation target
compileTest: setupTest\
	     $(addsuffix .o, $(basename $(DEPEND)))\
	     cleanTest
	# Compilation 
	@echo "Compiling $(TEST_NAME)" 
	gcc -g3 -o $(TEST_NAME)\
	     	   $(notdir $(addsuffix .o, $(basename $(DEPEND))))
	@echo "Done."

# --- testparseArgs ---
testparseArgs:	parseArgs.c $(TEST_DIR)/testparseArgs.c setErrorInfo.c
	$(MAKE) -s compileTest DEPEND="$^" TEST_NAME=testparseArgs

# --- testsortInputCompare ---
testsortInputCompare:	sortInputCompare.c $(TEST_DIR)/testsortInputCompare.c
	$(MAKE) -s compileTest DEPEND="$^" TEST_NAME=testsortInputCompare
	
# --- teststrIgnoreCaseCmp ---
teststrIgnoreCaseCmp:	strIgnoreCaseCmp.s $(TEST_DIR)/teststrIgnoreCaseCmp.c
	$(MAKE) -s compileTest DEPEND="$^" TEST_NAME=teststrIgnoreCaseCmp

# --- testfindUniq ---
testfindUniq:	findUniq.c $(TEST_DIR)/testfindUniq.c setErrorInfo.c\
	strIgnoreCaseCmp.s
	$(MAKE) -s compileTest DEPEND="$^" TEST_NAME=testfindUniq

# --- testparseInputStream ---
testparseInputStream: parseInputStream.c $(TEST_DIR)/testparseInputStream.c\
	setErrorInfo.c sortInputCompare.c
	$(MAKE) -s compileTest DEPEND="$^" TEST_NAME=testparseInputStream

