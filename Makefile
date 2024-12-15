# This file is subject to the terms and conditions of the GNU General Public
# License. See the file COPYING in the main directory of this archive for
# more details.

CC=gcc
CFLAGS += -std=c11
CFLAGS += -Wall -Wextra -Werror -Wpedantic
CFLAGS += -pedantic-errors
CFLAGS += -Waggregate-return
CFLAGS += -Wbad-function-cast
CFLAGS += -Wcast-align
CFLAGS += -Wcast-qual
CFLAGS += -Wfloat-equal
CFLAGS += -Wformat=2
CFLAGS += -Wlogical-op
CFLAGS += -Wmissing-declarations
CFLAGS += -Wmissing-include-dirs
CFLAGS += -Wmissing-prototypes
CFLAGS += -Wnested-externs
CFLAGS += -Wpointer-arith
CFLAGS += -Wredundant-decls
CFLAGS += -Wsequence-point
CFLAGS += -Wshadow
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wswitch
CFLAGS += -Wundef
CFLAGS += -Wunreachable-code
CFLAGS += -Wunused-but-set-parameter
CFLAGS += -Wwrite-strings

TARGET = charoln.a

$(TARGET): charoln.o
	@ar rcs $@ charoln.o

charoln.o: charoln.c charoln.h
	@$(CC) $(CFLAGS) -c -o $@ $<

test:
	@$(CC) $(CFLAGS) charoln.c ./tests/test.c -DTESTING -g -O2 -o tests.out
	@./tests.out
	@ rm tests.out

clean:
	@rm -f *.o *.a *.out $(TARGET)
