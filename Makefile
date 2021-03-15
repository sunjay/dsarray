SRC_DIR := src
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
LIB := $(BUILD_DIR)/libdsarray.a $(BUILD_DIR)/libdsarray.so

CC = clang
AR = ar
CFLAGS = -Wall -Wextra -MMD -MP -Iinclude

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean test
.PRECIOUS: %.o
.SECONDARY: $(OBJ)

all: $(LIB)

%.a: $(OBJ) | $(BUILD_DIR)
	$(AR) rcs $@ $^

%.so: $(OBJ) | $(BUILD_DIR)
	$(CC) -shared -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	$(MAKE) -C tests clean
	@$(RM) -rv $(OBJ_DIR) $(BUILD_DIR)

test: $(LIB)
	$(MAKE) -C tests

-include $(OBJ:.o=.d)
