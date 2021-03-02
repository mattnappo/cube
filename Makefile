CC    := gcc
FLAGS := -Wall -g -lm

SOURCES := $(shell find src -name '*.c')
HEADERS := $(shell find src -name '*.h')

TEST_SRCS    := $(wildcard tests/*.c)
TEST_TARGETS := $(basename $(notdir $(TEST_SRCS)))

INCLUDE := -Isrc -I.

cube.out: main.c $(SOURCES) $(HEADERS)
	mkdir -p bin/
	gcc $(FLAGS) -o bin/$@ $< $(SOURCES) $(INCLUDE)

tests: $(TEST_TARGETS)

$(TEST_TARGETS): $(SOURCES) $(HEADERS)

%: tests/%.c
	mkdir -p bin/tests
	$(CC) $(FLAGS) -o bin/tests/$@.out $(SOURCES) $< $(INCLUDE)

.PHONY: clean
clean:
	rm -rf bin/*
