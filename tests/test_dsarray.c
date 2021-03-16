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
        int *top_ptr = dsarray_last(&arr);
        TEST_ASSERT_NOT_NULL(top_ptr);
        int top = *top_ptr;
        dsarray_pop(&arr);

        // Check that we got the right value
        TEST_ASSERT_EQUAL_INT(curr, top);

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

void test_no_over_allocate(void) {
    // Make sure it is possible to allocate exactly as much as there is capacity

    dsarray arr;
    dsarray_new(&arr, sizeof(int));

    TEST_ASSERT_EQUAL_UINT(0, dsarray_len(&arr));

    for (int i = 0; ; i++) {
        dsarray_push(&arr, &i);

        if (dsarray_capacity(&arr) >= 100 && dsarray_len(&arr) != dsarray_capacity(&arr)) {
            break;
        }
    }

    // Make sure we start out with a length less than and NOT equal to the capacity
    TEST_ASSERT_TRUE(dsarray_len(&arr) < dsarray_capacity(&arr));

    // Push exactly enough items to get up to the capacity
    size_t remaining = dsarray_capacity(&arr) - dsarray_len(&arr);
    for (int i = 0; (size_t)i < remaining; i++) {
        dsarray_push(&arr, &i);
    }

    // The length and the capacity should be equal now
    TEST_ASSERT_EQUAL_UINT(dsarray_len(&arr), dsarray_capacity(&arr));

    dsarray_destroy(&arr);
}

void test_insert(void) {
    dsarray arr;
    dsarray_new(&arr, sizeof(int));

    TEST_ASSERT_EQUAL_UINT(0, dsarray_len(&arr));

    // Continuously insert at the front of the array
    for (int i = 0; i < 100; i++) {
        TEST_ASSERT_EQUAL_UINT(i, dsarray_len(&arr));

        dsarray_insert(&arr, 0, &i);
        TEST_ASSERT_EQUAL_INT(i, *(int*)dsarray_first(&arr));

        TEST_ASSERT_EQUAL_UINT(i+1, dsarray_len(&arr));
    }

    // Values should be reversed
    for (int i = 0; i < 100; i++) {
        int *top_ptr = dsarray_last(&arr);
        TEST_ASSERT_NOT_NULL(top_ptr);
        int top = *top_ptr;
        dsarray_pop(&arr);

        TEST_ASSERT_EQUAL_INT(i, top);
        TEST_ASSERT_EQUAL_UINT(100-i-1, dsarray_len(&arr));
    }

    TEST_ASSERT_TRUE(dsarray_is_empty(&arr));

    // Push some values
    for (int value = 0; value < 4; value += 1) {
        dsarray_push(&arr, &value);
    }

    // Insert in the middle
    int value = -1;
    dsarray_insert(&arr, dsarray_len(&arr)/2, &value);

    // Should be exactly the 5 values we expect
    TEST_ASSERT_EQUAL_UINT(5, dsarray_len(&arr));
    TEST_ASSERT_EQUAL_INT(0, *(int*)dsarray_get(&arr, 0));
    TEST_ASSERT_EQUAL_INT(1, *(int*)dsarray_get(&arr, 1));
    TEST_ASSERT_EQUAL_INT(-1, *(int*)dsarray_get(&arr, 2));
    TEST_ASSERT_EQUAL_INT(2, *(int*)dsarray_get(&arr, 3));
    TEST_ASSERT_EQUAL_INT(3, *(int*)dsarray_get(&arr, 4));

    // Insert at the end
    value = -99;
    dsarray_insert(&arr, dsarray_len(&arr), &value);
    TEST_ASSERT_EQUAL_INT(-99, *(int*)dsarray_last(&arr));

    dsarray_destroy(&arr);
}

void test_remove(void) {
    dsarray arr;
    dsarray_new(&arr, sizeof(int));

    TEST_ASSERT_EQUAL_UINT(0, dsarray_len(&arr));

    // Push some values
    for (int value = 0; value < 5; value += 1) {
        dsarray_push(&arr, &value);
    }

    TEST_ASSERT_EQUAL_UINT(5, dsarray_len(&arr));
    TEST_ASSERT_EQUAL_INT(0, *(int*)dsarray_get(&arr, 0));
    TEST_ASSERT_EQUAL_INT(1, *(int*)dsarray_get(&arr, 1));
    TEST_ASSERT_EQUAL_INT(2, *(int*)dsarray_get(&arr, 2));
    TEST_ASSERT_EQUAL_INT(3, *(int*)dsarray_get(&arr, 3));
    TEST_ASSERT_EQUAL_INT(4, *(int*)dsarray_get(&arr, 4));

    // Remove an item from the middle
    dsarray_remove(&arr, 2);

    TEST_ASSERT_EQUAL_UINT(4, dsarray_len(&arr));
    TEST_ASSERT_EQUAL_INT(0, *(int*)dsarray_get(&arr, 0));
    TEST_ASSERT_EQUAL_INT(1, *(int*)dsarray_get(&arr, 1));
    TEST_ASSERT_EQUAL_INT(3, *(int*)dsarray_get(&arr, 2));
    TEST_ASSERT_EQUAL_INT(4, *(int*)dsarray_get(&arr, 3));

    // Remove an item from the end
    dsarray_remove(&arr, dsarray_len(&arr)-1);

    TEST_ASSERT_EQUAL_UINT(3, dsarray_len(&arr));
    TEST_ASSERT_EQUAL_INT(0, *(int*)dsarray_get(&arr, 0));
    TEST_ASSERT_EQUAL_INT(1, *(int*)dsarray_get(&arr, 1));
    TEST_ASSERT_EQUAL_INT(3, *(int*)dsarray_get(&arr, 2));

    // Remove an item from the start
    dsarray_remove(&arr, 0);

    TEST_ASSERT_EQUAL_UINT(2, dsarray_len(&arr));
    TEST_ASSERT_EQUAL_INT(1, *(int*)dsarray_get(&arr, 0));
    TEST_ASSERT_EQUAL_INT(3, *(int*)dsarray_get(&arr, 1));

    dsarray_destroy(&arr);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_empty_array);
    RUN_TEST(test_simple_push_get);
    RUN_TEST(test_array_as_stack);
    RUN_TEST(test_no_over_allocate);
    RUN_TEST(test_insert);
    RUN_TEST(test_remove);

    return UNITY_END();
}
