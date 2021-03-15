# dsarray - Dynamically-sized Array in C

[![CI](https://github.com/sunjay/dsarray/actions/workflows/dsarray.yml/badge.svg)](https://github.com/sunjay/dsarray/actions/workflows/dsarray.yml)

This is an implementation of a dynamically sized array in C. It uses `void *` to simulate
"polymorphism" so you do not need to redefine the array every time you need to use it for a
different type. To make this work, you need to pass in the size of the type you are storing when
you create the array.

```c
dsarray items;
dsarray_new(&items, sizeof(int));

// Push an item into the array
int value = 3;
dsarray_push(&items, &value);

// Get the item from the array and print it
int *item = dsarray_get(&items, 0);
printf("%d\n", *item);
```

## Building

Run `make` from the project's root directory.

This will generate `build/libdsarray.a` and `build/libdsarray.so`.

## Running Tests

Run `make test` from the project's root directory.

This will run the unit tests in the `tests` directory.
