#include "dsarray.h"

#include <stdlib.h> // realloc
#include <string.h> // memmove

// Based on: https://stackoverflow.com/a/10143264/551904
__attribute__ ((const))
static inline size_t next_power_of_2(size_t x) {
    if (x == 0) {
        return 1;
    } else {
        // Only works on 64-bit platforms
        return ((size_t)1) << (64 - __builtin_clzl(x));
    }
}

void dsarray_new(dsarray *arr, size_t el_size) {
    dsarray_with_capacity(arr, el_size, 0);
}

void dsarray_with_capacity(dsarray *arr, size_t el_size, size_t capacity) {
    arr->data = NULL;
    arr->length = 0;
    arr->capacity = capacity;
    arr->el_size = el_size;

    dsarray_reserve(arr, capacity);
}

void dsarray_destroy(dsarray *arr) {
    free(arr->data);
}

bool dsarray_is_empty(dsarray *arr) {
    return dsarray_len(arr) == 0;
}

size_t dsarray_len(dsarray *arr) {
    return arr->length;
}

size_t dsarray_capacity(dsarray *arr) {
    return arr->capacity;
}

void *dsarray_get(dsarray *arr, size_t index) {
    if (index >= dsarray_len(arr)) {
        return NULL;
    }
    return dsarray_get_unchecked(arr, index);
}

void *dsarray_get_unchecked(dsarray *arr, size_t index) {
    return arr->data + index * arr->el_size;
}

void *dsarray_first(dsarray *arr) {
    return dsarray_get(arr, 0);
}

void *dsarray_last(dsarray *arr) {
    // (0-1) == MAX, which will be out of bounds anyway and return NULL
    return dsarray_get(arr, dsarray_len(arr)-1);
}

void dsarray_push(dsarray *arr, void *item) {
    // Make sure there is space for at least one element
    dsarray_reserve(arr, 1);

    // Get the uninitialized slot for the item one past the end of the array
    void *slot = dsarray_get_unchecked(arr, arr->length);
    memmove(slot, item, arr->el_size);

    // Now that it is initialized, the slot can be used safely
    arr->length += 1;
}

void dsarray_pop(dsarray *arr) {
    arr->length -= 1;
}

void dsarray_insert(dsarray *arr, size_t index, void *item) {
    //TODO
}

void dsarray_remove(dsarray *arr, size_t index) {
    //TODO
}

void dsarray_clear(dsarray *arr) {
    //TODO
}

void dsarray_reserve(dsarray *arr, size_t additional) {
    if (additional == 0) return;

    size_t target_capacity = dsarray_len(arr)+additional;

    // Do nothing if there is already enough space
    if (target_capacity < dsarray_capacity(arr)) {
        return;
    }

    // Round capacity to the next power of 2 to avoid frequent reallocations
    // Since additional >= 1, `target_capacity-1` will be >= 0
    target_capacity = next_power_of_2(target_capacity-1);

    // Allocate enough space for `target_capacity` elements and copy over the old data if any
    arr->data = realloc(arr->data, target_capacity * arr->el_size);
    if (!arr->data) {
        abort();
    }
    arr->capacity = target_capacity;
}

void dsarray_shrink_to_fit(dsarray *arr) {
    //TODO
}

void dsarray_truncate(dsarray *arr, size_t len) {
    //TODO
}
