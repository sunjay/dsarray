#include "dsarray.h"

dsarray dsarray_new(size_t el_size) {
    return dsarray_with_capacity(el_size, 0);
}

dsarray dsarray_with_capacity(size_t el_size, size_t capacity) {
    dsarray arr = {
        .data = NULL,
        .length = 0,
        .capacity = capacity,
        .el_size = el_size,
    };

    return arr;
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
    //TODO
}

void dsarray_pop(dsarray *arr) {
    //TODO
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
    //TODO
}

void dsarray_shrink_to_fit(dsarray *arr) {
    //TODO
}

void dsarray_truncate(dsarray *arr, size_t len) {
    //TODO
}
