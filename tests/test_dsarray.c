#include "unity.h"
#include "dsarray.h"

// set stuff up here
void setUp(void) {}

// clean stuff up here
void tearDown(void) {}

void test_empty_array(void) {
    dsarray arr;
    dsarray_new(&arr, sizeof(int));

    TEST_ASSERT_EQUAL_UINT(dsarray_len(&arr), 0);
    // Should not allocate when initially empty
    TEST_ASSERT_EQUAL_UINT(dsarray_capacity(&arr), 0);
    TEST_ASSERT_TRUE(dsarray_is_empty(&arr));

    dsarray_destroy(&arr);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_empty_array);

    return UNITY_END();
}
