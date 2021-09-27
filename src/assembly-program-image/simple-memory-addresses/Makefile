.PHONY: all clean

# Settings

MAKEFLAGS += --no-builtin-rules --no-builtin-variables

CC = gcc
CC_OPTS = -O0 -g -pie -fpie -Wall -Wextra
LD = gcc
LD_OPTS = -O0 -g -pie -fpie

# Files

ALL_EX = print-main-global print-main-local print-more-locals print-with-recursion
ALL_OO = $(addsuffix .o, $(ALL_EX))
ALL_DD = $(addsuffix .dep, $(ALL_EX))

# Rules

all: $(ALL_EX)

clean:
	rm -f *.o
	rm -f *.dep
	rm -f $(ALL_EX)

%: %.o
	$(LD) $^ $(LD_OPTS) -o $@

%.o: %.c
	$(CC) $(CC_OPTS) -c -o $@ $<

# Deps

-include $(ALL_DD)

%.dep: %.c
	$(CC) $(CC_OPTS) -MM -MT "$@ $(basename $@).o" -o $@ $<
