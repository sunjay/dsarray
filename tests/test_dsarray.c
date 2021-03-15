#include "unity.h"
#include "dsarray.h"

// set stuff up here
void setUp(void) {}

// clean stuff up here
void tearDown(void) {}

void test_empty_array(void) {
    dsarray arr;
    dsarray_new(&arr, sizeof(int));

    TEST_ASSERT_EQUAL_UINT(0, dsarray_len(&arr));
    TEST_ASSERT_TRUE(dsarray_is_empty(&arr));
    // Should not allocate when initially empty
    TEST_ASSERT_EQUAL_UINT(0, dsarray_capacity(&arr));

    dsarray_destroy(&arr);
}

void test_simple_push_get(void) {
    dsarray arr;
    dsarray_new(&arr, sizeof(int));

    TEST_ASSERT_EQUAL_UINT(0, dsarray_len(&arr));
    TEST_ASSERT_TRUE(dsarray_is_empty(&arr));
    // Should not allocate when initially empty
    TEST_ASSERT_EQUAL_UINT(0, dsarray_capacity(&arr));

    // Push an item into the array
    int value = 3;
    dsarray_push(&arr, &value);

    TEST_ASSERT_EQUAL_UINT(1, dsarray_len(&arr));
    TEST_ASSERT_FALSE(dsarray_is_empty(&arr));
    TEST_ASSERT_TRUE(dsarray_capacity(&arr) > 0);

    // Get the item from the array
    int *item = dsarray_get(&arr, 0);
    TEST_ASSERT_EQUAL_INT(3, *item);

    dsarray_destroy(&arr);
}

void test_array_as_stack(void) {
    dsarray arr;
    dsarray_new(&arr, sizeof(int));

    TEST_ASSERT_EQUAL_UINT(0, dsarray_len(&arr));
    TEST_ASSERT_TRUE(dsarray_is_empty(&arr));
    // Should not allocate when initially empty
    TEST_ASSERT_EQUAL_UINT(0, dsarray_capacity(&arr));

    // Push values onto the stack/array
    for (int value = 0; value < 10; value++) {
        dsarray_push(&arr, &value);
    }

    size_t expected_capacity = dsarray_capacity(&arr);
    TEST_ASSERT_EQUAL_UINT(10, dsarray_len(&arr));
    TEST_ASSERT_FALSE(dsarray_is_empty(&arr));
    TEST_ASSERT_TRUE(expected_capacity > 0);

    int curr = 9;
    while (!dsarray_is_empty(&arr)) {
        // Pop the top value off the stack
        int *top = dsarray_last(&arr);
        dsarray_pop(&arr);

        // Check that we got the right value
        TEST_ASSERT_NOT_NULL(top);
        TEST_ASSERT_EQUAL_INT(curr, *top);

        // Length should be decreasing
        TEST_ASSERT_EQUAL_UINT(curr, dsarray_len(&arr));
        // Capacity should not change
        TEST_ASSERT_EQUAL_UINT(expected_capacity, dsarray_capacity(&arr));

        curr -= 1;
    }

    // Array should be empty, but capacity should be the same
    TEST_ASSERT_EQUAL_UINT(0, dsarray_len(&arr));
    TEST_ASSERT_TRUE(dsarray_is_empty(&arr));
    TEST_ASSERT_EQUAL_UINT(expected_capacity, dsarray_capacity(&arr));

    dsarray_destroy(&arr);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_empty_array);
    RUN_TEST(test_simple_push_get);
    RUN_TEST(test_array_as_stack);

    return UNITY_END();
}
