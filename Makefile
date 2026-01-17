BINARY   := main
BUILD_DIR := build

INCLUDES := -Iinclude
LDLIBS := -lm

WARNINGS := -Wall -Wextra -Wpedantic -Wshadow -Wformat=2 -Wconversion \
            -Wunused-parameter -Wstrict-prototypes -Wmissing-prototypes \
            -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference \
            -Wcast-align=strict -Warray-parameter -Wstringop-overflow=4 -Werror
DEBUG := -Og -g3 -fno-omit-frame-pointer

ifeq ($(OS),Windows_NT)
    TARGET   := $(BINARY).exe
    RM := del /q
    MKDIR := if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
    RMDIR := rmdir /s /q
else
    TARGET := $(BINARY)

    RM := rm -f
    MKDIR := mkdir -p $(BUILD_DIR)
    RMDIR := rm -rf
endif

SRCS := $(wildcard *.c) $(wildcard src/*.c)
OBJS := $(patsubst %.c, build/%.o, $(notdir $(SRCS)))

vpath %.c src

all: $(TARGET) run

$(TARGET): $(OBJS)
	gcc $(WARNINGS) $(DEBUG) $(INCLUDES) $(LDLIBS) $(OBJS) -o $(TARGET) $(LDFLAGS)

build/%.o: %.c
	@$(MKDIR)
	$(CC) $(WARNINGS) $(DEBUG) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) $(TARGET)
	$(RMDIR) $(BUILD_DIR)

.PHONY: all run clean