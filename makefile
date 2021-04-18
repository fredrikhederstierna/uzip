EXE      := uzip_tester

WARNING  := -W -Wall -Wextra -Wno-unused-parameter -Wno-unused-but-set-variable -Wno-unused-variable
INCLUDE  := -I.
OPTIMIZE := -O2 -std=c99
DEBUG    := -g3 -ggdb3 -gdwarf-4 -fvar-tracking-assignments

CFLAGS   := $(OPTIMIZE) $(INCLUDE) $(WARNING) $(DEBUG)
LDFLAGS  := -lm -lc -lgcc
CVPATH   := $(INCLUDE) .

vpath   %.c $(CVPATH)

CFILES	+= uzip_main.c
CFILES	+= bitvec.c

all:
	@echo "Compiling..."
	gcc -o $(EXE) $(CFILES) $(CFLAGS) $(LDFLAGS)

clean:
	@echo "Cleaning..."
	rm -rf $(EXE) *.o
