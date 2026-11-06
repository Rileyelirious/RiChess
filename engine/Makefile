CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -g -Iinclude -MMD -MP
SRC     = $(wildcard src/*.c)
OBJ     = $(SRC:src/%.c=build/%.o)

build/engine: $(OBJ)
	$(CC) $^ -o $@

build/%.o: src/%.c
	@mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build

run: build/engine
	./build/engine

-include $(OBJ:.o=.d)
.PHONY: clean