#pragma once

#include <stdint.h> // int*_t, uint*_t
#include <stddef.h> // size_t, NULL
#include <stdbool.h> // bool

/// Destroy the given item
///
/// This will be called on every item just before it is removed from the array.
/// Items that have been passed to this function must not be accessed afterwards.
typedef void (*op_drop)(void *a);

/// Move the given item into the given uninitialized destination slot
///
/// This will be called when the `item` pointer does not need to be preserved during a copy.
///
/// The argument pointers are guaranteed to be unique. This function is not expected to have any
/// side-effects.
typedef void (*op_move)(void *dest, void *item);

/// Copy the given item into the given uninitialized destination slot
///
/// This will be called when the original item pointer must remain valid for use.
///
/// The argument pointers are guaranteed to be unique. This function is not expected to have any
/// side-effects.
typedef void (*op_copy)(void *dest, void *item);

/// Comparator function for comparing two items stored in the array
///
/// The two addresses provided as arguments are not guaranteed to be unique. This function is
/// expected to not have any side-effects. It should not modify the items in any way.
///
/// Return value interpretation:
///
/// * < 0 - The item at `a` goes before the item at `b`
/// * = 0 - The item at `a` is equivalent to the item at `b`
/// * > 0 - The item at `a` goes after the item at `b`
typedef int8_t (*op_cmp)(void *a, void *b);

/// Test for total equality between two items stored in the array
///
/// The two addresses provided as arguments are not guaranteed to be unique. This function is
/// expected to not have any side-effects. It should not modify the items in any way.
///
/// Returns true if the item at `a` is equal to the item at `b`, and returns false otherwise.
typedef bool (*op_eq)(void *a, void *b);

/// Print the given item to stdout
///
/// This function is not expected to modify the item in any way.
///
/// Assumes that just the item will be printed, without any trailing newline
typedef void (*op_print)(void *a);

/// A virtual-dispatch table for items stored in a dynamically-sized array
///
/// Any member may be NULL, in which case a default action will be taken. Some array operations may
/// not be supported unless certain vtable entries are present.
typedef struct {
    op_drop drop;

    op_move move;
    op_copy copy;

    op_cmp cmp;
    op_eq eq;

    op_print print;
} dsvtable;

//// vtables for standard types provided by this library ////

#include "std_dsvtables.h"
