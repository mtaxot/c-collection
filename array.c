#include"array.h"

void array_init(array *array)
{
    assert(array != NULL);
    array->size = 0;
    array->capacity = ARRAY_INIT_CAPACITY;
    array->table = (array_item**)malloc(ARRAY_INIT_CAPACITY * sizeof(array_item**));
    assert(array->table != NULL);
    memset(array->table, 0, ARRAY_INIT_CAPACITY * sizeof(array_item**));
}

size_t get_array_size(array *array)
{
    assert(array != NULL);
    return array->size;
}

int array_insert_before(array *array, int index, void *item)
{
    assert(array != NULL);
    if(index >= array->size || item == NULL || index < 0)
    {
        return OP_ARRAY_FAIL;
    }
    if(array->size >= array->capacity)
    {
        //no capacity, need realloc.
        size_t new_capacity = array->capacity + array->capacity / 2;
        array_item **newtable = (array_item**)realloc(array->table, new_capacity * sizeof(array_item**));
        if(newtable == NULL)
        {
            //no memory.
            return OP_ARRAY_FAIL;
        }
        else
        {
            array->table = newtable;
            array->capacity = new_capacity;
        }
    }
    //do insert.
    int i;
    for(i = array->size; i >= index; --i)
    {
        array->table[i] = array->table[i - 1];
    }
    array->table[index] = (array_item*)item;
    ++(array->size);
    return OP_ARRAY_SUCCESS;
}

int array_index_of(array *array, void *item)
{
    assert(array != NULL);
    int i, index = OP_ARRAY_FAIL;
    if(item == NULL)
    {
        return OP_ARRAY_FAIL;
    }
    for(i = 0; i < array->size; ++i)
    {
        if(array->table[i] == (array_item*)item)
        {
            index = i;
            break;
        }
    }
    return index;
}

array_item *array_remove_last(array *array)
{
    assert(array != NULL);
    if(array->size <= 0)
    {
        return NULL;
    }
    array_item *last = array->table[array->size - 1];
    --(array->size);
    return last;
}

array_item *array_remove_first(array *array)
{
    assert(array != NULL);
    if(array->size <= 0)
    {
        return NULL;
    }
    array_item *first = array->table[0];
    int i;
    for(i = 1; i < array->size; ++i)
    {
        array->table[i - 1] = array->table[i];
    }
    --(array->size);
    return first;
}

array_item *array_remove_by_index(array *array, int index)
{
    assert(array != NULL);
    if(index < 0 || index >= array->size)
    {
        return NULL;
    }
    array_item *item = array->table[index];
    int i;
    for(i = index + 1; i < array->size; ++i)
    {
        array->table[i - 1] = array->table[i];
    }
    --(array->size);
    return item;
}

array_item *array_find_by_index(array *array, size_t index)
{
    assert(array != NULL);
    if(index < array->size)
    {
        return array->table[index];
    }
    return NULL;
}


int array_push_back(array *array, void *item)
{
    assert(array != NULL);
    if(array->size < array->capacity)
    {
        //have capacity.
        array->table[array->size] = (array_item*) item;
        ++(array->size);
        return OP_ARRAY_SUCCESS;
    }
    else
    {
        //no capacity, need realloc.
        size_t new_capacity = array->capacity + array->capacity / 2;
        array_item **newtable = (array_item**)realloc(array->table, new_capacity * sizeof(array_item**));
        if(newtable != NULL)
        {
            array->table = newtable;
            array->capacity = new_capacity;
            array->table[array->size] = (array_item*) item;
            ++(array->size);
            return OP_ARRAY_SUCCESS;
        }
        else
        {
            //no memory.
            return OP_ARRAY_FAIL;
        }
    }
}

void array_free_shallow(array *array)
{
    assert(array != NULL);
    free(array->table);
    array->size = 0;
    array->capacity = 0;
    array->table = NULL;
}


void array_free_deep(array *array)
{
    assert(array != NULL);
    int i;
    for(i = 0; i < array->size; ++i)
    {
        if(array->table[i] != NULL)
        {
            free(array->table[i]);
        }
    }
    free(array->table);
    array->size = 0;
    array->capacity = 0;
    array->table = NULL;
}

