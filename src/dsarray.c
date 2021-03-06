#include "dsarray.h"

#include <stdlib.h> // realloc, free
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

void dsarray_init(dsarray *arr, size_t el_size) {
    dsarray_init_capacity(arr, el_size, 0);
}

void dsarray_init_capacity(dsarray *arr, size_t el_size, size_t capacity) {
    dsarray_init_vtable_capacity(arr, el_size, NULL, capacity);
}

void dsarray_init_vtable(dsarray *arr, size_t el_size, dsvtable *vtable) {
    dsarray_init_vtable_capacity(arr, el_size, vtable, 0);
}

void dsarray_init_vtable_capacity(dsarray *arr, size_t el_size, dsvtable *vtable, size_t capacity) {
    arr->el_size = el_size;
    arr->vtable = vtable;
    arr->data = NULL;
    arr->length = 0;
    arr->capacity = capacity;

    dsarray_reserve(arr, capacity);
}

void dsarray_destroy(dsarray *arr) {
    free(arr->data);
    arr->data = NULL;
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
    // Make sure there is space for at least one element
    dsarray_reserve(arr, 1);

    size_t len = dsarray_len(arr);

    // Move all elements from the index onwards into the next slot
    // Need to do this while iterating backwards to avoid overlap
    // Fancy loop accounts for unsigned type: https://stackoverflow.com/a/665773/551904
    for (size_t i = len; i-- > index;) {
        void *curr_item = dsarray_get_unchecked(arr, i);
        // This is will always be memory we consider "uninitialized"
        void *next_item = dsarray_get_unchecked(arr, i+1);
        memmove(next_item, curr_item, arr->el_size);
    }

    // Put the item into its slot, now that the slot is empty
    void *slot = dsarray_get_unchecked(arr, index);
    memmove(slot, item, arr->el_size);

    arr->length += 1;
}

void dsarray_remove(dsarray *arr, size_t index) {
    size_t len = dsarray_len(arr);

    // Move all elements from the index onwards to the previous slot
    for (size_t i = index; i < len; i++) {
        void *curr_item = dsarray_get_unchecked(arr, i);
        void *next_item = dsarray_get_unchecked(arr, i+1);
        memmove(curr_item, next_item, arr->el_size);
    }

    arr->length -= 1;
}

void dsarray_clear(dsarray *arr) {
    arr->length = 0;
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
    size_t len = dsarray_len(arr);

    if (len > 0) {
        arr->data = realloc(arr->data, len * arr->el_size);
        if (!arr->data) {
            abort();
        }
    } else {
        free(arr->data);
        // Need this to avoid double free
        arr->data = NULL;
    }

    arr->capacity = len;
}

void dsarray_truncate(dsarray *arr, size_t len) {
    if (len < dsarray_len(arr)) {
        arr->length = len;
    }
}
