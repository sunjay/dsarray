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
    // Should not allocate when initially empty
    TEST_ASSERT_EQUAL_UINT(0, dsarray_capacity(&arr));
    TEST_ASSERT_TRUE(dsarray_is_empty(&arr));

    dsarray_destroy(&arr);
}

void test_simple_push_get(void) {
    dsarray arr;
    dsarray_new(&arr, sizeof(int));

    TEST_ASSERT_EQUAL_UINT(0, dsarray_len(&arr));
    // Should not allocate when initially empty
    TEST_ASSERT_EQUAL_UINT(0, dsarray_capacity(&arr));
    TEST_ASSERT_TRUE(dsarray_is_empty(&arr));

    // Push an item into the array
    int value = 3;
    dsarray_push(&arr, &value);

    TEST_ASSERT_EQUAL_UINT(1, dsarray_len(&arr));
    TEST_ASSERT_TRUE(dsarray_capacity(&arr) > 0);
    TEST_ASSERT_FALSE(dsarray_is_empty(&arr));

    // Get the item from the array
    int *item = dsarray_get(&arr, 0);
    TEST_ASSERT_EQUAL_INT(3, *item);

    dsarray_destroy(&arr);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_empty_array);
    RUN_TEST(test_simple_push_get);

    return UNITY_END();
}
