# dsarray - Dynamically-sized Array in C

This is an implementation of a dynamically sized array in C. It uses `void *` to simulate
"polymorphism" so you do not need to redefine the array every time you need to use it for a
different type. To make this work, you need to pass in the size of the type you are storing when
you create the array.

```c
dsarray items = dsarray_new(sizeof(int));
dsarray_push(&items, &3);
int *item = dsarray_get(&items, 0);
printf("%d\n", *item);
```

## Building

Run `make`. This will generate `build/libdsarray.a` and `build/libdsarray.so`.
