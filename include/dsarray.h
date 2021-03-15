#pragma once

#include <stddef.h> // size_t, NULL
#include <stdbool.h> // bool

/// A dynamically-sized array of data
typedef struct {
    /// Pointer to the allocated data
    void *data;
    /// The number of items of size `el_size` currently in use
    size_t length;
    /// The total number of items of size `el_size` that can be stored in `data`
    size_t capacity;
    /// The size of each element in the array
    size_t el_size;
} dsarray;

/// Initializes `arr` as an empty dynamically-sized array
void dsarray_new(dsarray *arr, size_t el_size);

/// Initializes `arr` as an empty dynamically-sized array with at least the given capacity
void dsarray_with_capacity(dsarray *arr, size_t el_size, size_t capacity);

/// Frees a dynamically-sized array
///
/// Undefined behavior to use an array after it was passed to this function
void dsarray_destroy(dsarray *arr);

/// Returns true if the array is empty
bool dsarray_is_empty(dsarray *arr);

/// Returns the number of items in the array
size_t dsarray_len(dsarray *arr);

/// Returns the number of items the array can hold without reallocating
size_t dsarray_capacity(dsarray *arr);

/// Gets an item from the array at the given index
///
/// Returns NULL if the index is out of bounds
void *dsarray_get(dsarray *arr, size_t index);

/// Gets an item from the array at the given index
///
/// Undefined behavior if the index is out of bounds
void *dsarray_get_unchecked(dsarray *arr, size_t index);

/// Gets the first item in the array or NULL if the array is empty
void *dsarray_first(dsarray *arr);

/// Gets the last item in the array or NULL if the array is empty
void *dsarray_last(dsarray *arr);

/// Pushes an item into the array
void dsarray_push(dsarray *arr, void *item);

/// Removes the last element from the array
///
/// Use `dsarray_last` to get a copy of the value before it is removed.
void dsarray_pop(dsarray *arr);

/// Inserts an element at position `index`, shifting all elements after it to the right.
///
/// May reallocate if len == capacity.
///
/// Undefined behavior if the index is out of bounds
void dsarray_insert(dsarray *arr, size_t index, void *item);

/// Removes the element at position `index`, shifting all elements after it to the left.
///
/// Use `dsarray_get` to get a copy of the value before it is removed.
///
/// Undefined behavior if the index is out of bounds
void dsarray_remove(dsarray *arr, size_t index);

/// Clears the array, removing all values
///
/// Note that this method has no affect on the allocated capacity of the array.
void dsarray_clear(dsarray *arr);

/// Reserves capacity for at least `additional` more elements to be inserted.
///
/// The collection may reserve more space to avoid frequent reallocations. After calling `reserve`,
/// capacity will be greater than or equal to len + additional. Does nothing if capacity is
/// already sufficient.
void dsarray_reserve(dsarray *arr, size_t additional);

/// Shrinks the capacity of the array as much as possible.
///
/// It will drop down as close as possible to the length but the allocator may still inform the
/// array that there is space for a few more elements.
void dsarray_shrink_to_fit(dsarray *arr);

/// Shortens the array, keeping the first `len` elements and dropping the rest.
///
/// If `len` is greater than the array's current length, this has no effect.
///
/// Note: this method has no effect on the allocated capacity of the array.
void dsarray_truncate(dsarray *arr, size_t len);
