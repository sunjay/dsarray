#include "unity.h"
#include "dsarray.h"

// set stuff up here
void setUp(void) {}

// clean stuff up here
void tearDown(void) {}

void test_vtables_exist(void) {
    dsarray arr;

    // This test just "uses" each variable so we know it is defined
    #define TABLES 14
    dsvtable *tables[] = {
        &vtable_int8_t,
        &vtable_int16_t,
        &vtable_int32_t,
        &vtable_int64_t,

        &vtable_uint8_t,
        &vtable_uint16_t,
        &vtable_uint32_t,
        &vtable_uint64_t,

        &vtable_float,
        &vtable_double,

        &vtable_char,
        &vtable_bool,

        &vtable_size_t,

        &vtable_file,

        // Used to test that TABLES is correct
        NULL
    };

    int i;
    for (i = 0; i < TABLES; i++) {
        dsvtable *vtable = tables[i];
        TEST_ASSERT_NOT_NULL_MESSAGE(vtable, "TABLES is not set correctly");

        // This sizeof(...) is not correct, but we don't use the array so it doesn't matter
        dsarray_init_vtable(&arr, sizeof(int), vtable);

        TEST_ASSERT_EQUAL_PTR(arr.vtable, vtable);

        dsarray_destroy(&arr);
    }

    TEST_ASSERT_NULL_MESSAGE(tables[i], "TABLES is not set correctly");
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_vtables_exist);

    return UNITY_END();
}
