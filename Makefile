#
# Makefile template for CSE 30 -- PA1
#

#
# You need to change these next lines for each assignment
#

HEADERS		= pa1.h pa1Strings.h

C_SRCS		= pa1.c

ASM_SRCS	= printChar.s checkRange.s drawXOR.s line.s isOdd.s isNegative.s

C_OBJS		= pa1.o

ASM_OBJS	= printChar.o checkRange.o drawXOR.o line.o isOdd.o isNegative.o

OBJS		= ${C_OBJS} ${ASM_OBJS}

EXE		= pa1

#
# You should not need to change anything below this line
#

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

GCC_FLAGS	= -c -g -Wall -D__EXTENSIONS__
LINT_FLAGS1	= -c -err=warn
LINT_FLAGS2	= -u -x -err=warn
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
# Simply have our project target be a single default $(EXE) executable.
#

$(EXE):	$(OBJS)
	@echo "2nd phase lint on all C source files ..."
	$(LINT) $(LINT_FLAGS2) *.ln
	@echo ""
	@echo "Linking all object modules ..."
	$(GCC) -o $(EXE) $(LD_FLAGS) $(OBJS)
	@echo ""
	@echo "Done."

${C_OBJS}:      ${HEADERS}


clean:
	@echo "Cleaning up project directory ..."
	/usr/bin/rm -f *.o $(EXE) *.ln core a.out \
	    testcheckRange testisOdd testisNegative testprintChar testline
	@echo ""
	@echo "Clean."

testcheckRange:	test.h pa1.h isNegative.s checkRange.s testcheckRange.c
	@echo "Compiling testcheckRange.c"
	gcc -g -o testcheckRange testcheckRange.c checkRange.s isNegative.s
	@echo "Done."

runtestcheckRange: testcheckRange
	@echo "Running testcheckRange"
	@./testcheckRange

testisNegative:	test.h pa1.h isNegative.s testisNegative.c
	@echo "Compiling testisNegative.c"
	gcc -g -o testisNegative testisNegative.c isNegative.s
	@echo "Done."

runtestisNegative: testisNegative
	@echo "Running testisNegative"
	@./testisNegative

testisOdd:	test.h pa1.h isOdd.s testisOdd.c
	@echo "Compiling testisOdd.c"
	gcc -g -o testisOdd testisOdd.c isOdd.s
	@echo "Done."

runtestisOdd: testisOdd
	@echo "Running testisOdd"
	@./testisOdd
new:
	make clean
	make

testprintChar: pa1.h printChar.s testprintChar.c
	@echo "Compiling testprintChar.c"
	gcc -g -o testprintChar testprintChar.c printChar.s
	@echo "Done."

runtestprintChar: testprintChar
	@echo "Running testprintChar"
	@./testprintChar

testline: pa1.h printChar.s line.s testline.c
	@echo "Compiling testline.c"
	gcc -g -o testline testline.c line.s printChar.s
	@echo "Done."
