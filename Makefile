## Makefile template for CSE 30 -- PA3(anagrams)
#

HEADERS		= pa3.h pa3Strings.h test.h

C_SRCS		= setupDB.c createAnagram.c lowerCaseSortString.c pa3.c parseArgs.c \
						setErrorInfo.c writeAnagramToDB.c usage.c	findAnagrams.c \
						printErrors.c parseDB.c readAnagramFromDB.c userInterface.c \
						pa3Globals.c

C_SRCS_EC	= setupDB_ec.c createAnagram_ec.c lowerCaseSortString.c pa3.c \
						parseArgs.c setErrorInfo.c writeAnagramToDB.c usage.c	\
						findAnagrams.c printErrors.c parseDB.c readAnagramFromDB.c \
						userInterface_ec.c pa3Globals.c

ASM_SRCS	= charCompare.s hashString.s hashKeyMemberCompare.s\
						anagramCompare.s

C_OBJS		= $(C_SRCS:.c=.o)

C_OBJS_EC	= $(C_SRCS_EC:.c=.o)

ASM_OBJS	= $(ASM_SRCS:.s=.o)

OBJS			= $(C_OBJS) $(ASM_OBJS)

OBJS_EC 	= $(C_OBJS_EC) $(ASM_OBJS)

EXE				= anagrams

EXE_EC		= anagrams_ec

TEST_SRCS = testcharCompare.c testhashString.c testlowerCaseSortString.c\
						testcreateAnagram.c testsetupDB.c testwriteAnagramToDB.c

TEST_EXE	= $(TEST_SRCS:.c=)  

TEST_DIR	= unit_tests

# Default make on ieng9 does not implement GNU make functions
MAKE = gmake

#
# Relevant man pages:
#
# man gcc
# man as
# man lint
#

GCC		= gcc
ASM		= $(GCC)
LINT		= lint

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

$(EXE):	$(OBJS)
	@echo "2nd phase lint on all C source files ..."
	$(LINT) $(LINT_FLAGS2) *.ln
	@echo ""
	@echo "Linking all object modules ..."
	$(GCC) -o $(EXE) $(LD_FLAGS) $(OBJS)
	@echo ""
	@echo "Done."

$(EXE_EC): $(OBJS_EC)
	@echo "2nd phase lint on all C source files ..."
	$(LINT) $(LINT_FLAGS2) *.ln
	@echo ""
	@echo "Linking all object modules ..."
	$(GCC) -o $(EXE_EC) $(LD_FLAGS) $(OBJS_EC)
	@echo ""
	@echo "Done."

${C_OBJS}:      ${HEADERS}

clean:
	@echo "Cleaning up project directory ..."
	/usr/bin/rm -f *.o $(EXE) $(EXE_EC) $(TEST_EXE) anagram_database.db *.ln core
	@echo ""
	@echo "Clean."

new:
	make --no-print-directory clean
	make --no-print-directory

setupTest:
	# Move all headers into test directory
	echo ${addsuffix .o, ${basename ${DEPEND}}}
	cp $(HEADERS) $(TEST_DIR)

cleanTest:
	# Remove all header from test directory
	rm ${addprefix $(TEST_DIR)/,$(HEADERS)}

# --- TESTING ---
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

# --- testcharCompare ---
testcharCompare: charCompare.s $(TEST_DIR)/testcharCompare.c 
	$(MAKE) -s compileTest DEPEND="$^" TEST_NAME=testcharCompare 

# --- testcreateAnagram ---
testcreateAnagram: createAnagram.c $(TEST_DIR)/testcreateAnagram.c\
	lowerCaseSortString.c hashString.s charCompare.s pa3Globals.c
	$(MAKE) -s compileTest DEPEND="$^" TEST_NAME=testcreateAnagram 

# --- testlowerCaseSortString ---
testlowerCaseSortString: lowerCaseSortString.c\
	$(TEST_DIR)/testlowerCaseSortString.c charCompare.s
	$(MAKE) -s compileTest DEPEND="$^" TEST_NAME=testlowerCaseSortString 

# --- testhashString ---
testhashString: hashString.s $(TEST_DIR)/testhashString.c pa3Globals.c
	$(MAKE) -s compileTest DEPEND="$^" TEST_NAME=testhashString 

# --- testsetupDB ---
testsetupDB: setupDB.c $(TEST_DIR)/testsetupDB.c createAnagram.c\
	lowerCaseSortString.c hashString.s writeAnagramToDB.c setErrorInfo.c\
	pa3Globals.c charCompare.s
	$(MAKE) -s compileTest DEPEND="$^" TEST_NAME=testsetupDB 

# --- testwriteAnagramToDB ---
testwriteAnagramToDB: writeAnagramToDB.c $(TEST_DIR)/testwriteAnagramToDB.c
	$(MAKE) -s compileTest DEPEND="$^" TEST_NAME=testwriteAnagramToDB 

