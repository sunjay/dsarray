LIB := ../build/libdsarray.a
LIB_INCLUDE_DIR := ../include
TESTS_DIR := .
BUILD_DIR := ../build/tests
OBJ_DIR := $(BUILD_DIR)/obj
DEPS_DIR := $(BUILD_DIR)/deps

UNITY_DIR := lib/unity

DEPS := $(DEPS_DIR)/unity.o

CC = clang
CFLAGS = -Wall -Wextra -MMD -MP -I$(LIB_INCLUDE_DIR) -isystem$(UNITY_DIR)
LDFLAGS = -L../build

TESTS := $(wildcard $(TESTS_DIR)/*.c)
TESTS_OBJ := $(TESTS:$(TESTS_DIR)/%.c=$(OBJ_DIR)/%.o)
TEST_RUNNERS := $(TESTS:$(TESTS_DIR)/%.c=$(BUILD_DIR)/%)

.PHONY: run clean
.PRECIOUS: %.o
.SECONDARY: $(TESTS_OBJ)

run: $(TEST_RUNNERS)

$(BUILD_DIR)/%: $(OBJ_DIR)/%.o $(DEPS) $(LIB) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) $^ -o $@
	$@

$(OBJ_DIR)/%.o: $(TESTS_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(DEPS_DIR)/unity.o: $(UNITY_DIR)/unity.c | $(DEPS_DIR)
	$(CC) -I$(UNITY_DIR) -c $^ -o $@

$(BUILD_DIR) $(OBJ_DIR) $(DEPS_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(DEPS_DIR) $(OBJ_DIR) $(BUILD_DIR)

-include $(TESTS_OBJ:.o=.d)
