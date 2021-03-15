SRC_DIR := src
BUILD_DIR := build
OBJ_DIR := $(BUILD_DIR)/obj
LIB := $(BUILD_DIR)/dsarray.a $(BUILD_DIR)/dsarray.so

CC = clang
AR = ar
CFLAGS = -Wall -Wextra -MMD -MP -Iinclude

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean

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
	@$(RM) -rv $(OBJ_DIR) $(BUILD_DIR)

-include $(OBJ:.o=.d)
