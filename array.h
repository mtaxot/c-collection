#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>

#ifndef __ARRAY_H_
#define __ARRAY_H_

#define ARRAY_INIT_CAPACITY 16

typedef struct _array_item
{
    void *data;//private data.
}array_item;

typedef struct _array
{
    size_t size;
    size_t capacity;
    array_item **table;
}array;

#define AS_ARRAY_ITEM array_item __array_item

#define OP_ARRAY_SUCCESS (1)
#define OP_ARRAY_FAIL (-1)



#define array_for_each(array, temp, from)\
           for((temp) = *((array)->table + (from));\
                (from) < (array)->size;\
                  ++(from), (temp) = *((array)->table + (from)))


void array_init(array *array);

size_t get_array_size(array *array);

int array_insert_before(array *array, int index, void *item);

int array_index_of(array *array, void *item);

array_item *array_remove_last(array *array);

array_item *array_remove_first(array *array);

array_item *array_remove_by_index(array *array, int index);

array_item *array_find_by_index(array *array, size_t index);

int array_push_back(array *array, void *item);

void array_free_shallow(array *array);

void array_free_deep(array *array);

#endif

