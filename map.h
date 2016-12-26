#ifndef __MAP_H_
#define __MAP_H_
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>

/** special macro to specify a struct to be an entry of a map **/
#define AS_MAP_ENTRY map_entry __map_entry

/** return value indicates operating map success or fail **/
#define OP_MAP_SUCCESS (1)
#define OP_MAP_FAIL (-1)

/** this value recommand to be 2^n , the larger it is, the less conflict map will cause **/
#define DEFAULT_TABLE_SIZE 32

typedef struct _map_entry
{
    unsigned int hashcode;
    char *key;
    int key_size;
    struct _map_entry *next;
} map_entry;

typedef struct _map
{
    size_t __map_size;
    map_entry **table;
    unsigned int table_size;
    unsigned int (*hash)(char*, int);
    size_t conflict; // conflict times.
    size_t puts; // put operate times.
}map;

#define map_for_each(pmap, entry, _iii_) \
         for((_iii_) = 0; (_iii_) < (pmap)->table_size; ++(_iii_))\
             for((entry) = (pmap)->table[_iii_]; (entry) != NULL; (entry) = (entry)->next)\

// assess the no conflict, we recommand you to call this when map size equals spar, if you use
// map_init_custom(....) to init a map.
double get_conflict_ratio(map *map);

unsigned int hash(char *data, int len);// the default hash function implement.

void map_init(map *map);//init a map.

size_t map_size(map *map);//return map container size.

//init map with hash func. and table size default
void map_init_custom(map *map, size_t spar, unsigned int (*hashfunc)(char*,int));

//insert a "map_entry" type.
int map_put(map *map, char *key, int key_size, void *value);

//return value by key.
map_entry *map_get(map *map, char *key, int key_size);

void map_clear(map *map);

map_entry *map_remove(map *map, char *key, int key_size);

// free its own memory, not include its elements.
void map_free_shallow(map *map);

// free its own memory, associated with its elements.
void map_free_deep(map *map);
#endif
