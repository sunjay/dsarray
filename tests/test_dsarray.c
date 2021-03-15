#include "unity.h"
#include "dsarray.h"

// set stuff up here
void setUp(void) {}

// clean stuff up here
void tearDown(void) {}

void test_testing_framework(void) {
    dsarray arr = dsarray_new(sizeof(int));

    TEST_ASSERT_EQUAL_UINT(dsarray_len(&arr), 0);
    TEST_ASSERT_TRUE(dsarray_is_empty(&arr));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_testing_framework);

    return UNITY_END();
}
