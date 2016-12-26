#include "map.h"

//elf hash
unsigned int hash(char *data, int len)
{
    unsigned int hash = 0;
    unsigned int x = 0;
    unsigned int i = 0;
    char *str = data;
    for(i = 0; i < len; ++str, ++i)
    {
        hash = (hash << 4) + (*data);
        if((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
        }
        hash &= ~x;
    }
    return hash;
}

double get_conflict_ratio(map *map)
{
    assert(map != NULL);
    if(map->puts == 0) return 0.0;
    return (1.0 * map->conflict) / map->puts;
}

void map_init(map *map)
{
    assert(map != NULL);
    map->table = (map_entry**)malloc(DEFAULT_TABLE_SIZE * sizeof(map_entry*));
    assert(map->table != NULL);
    memset(map->table, 0, DEFAULT_TABLE_SIZE * sizeof(map_entry*));
    map->hash = hash;//default elf hash.
    map->table_size = DEFAULT_TABLE_SIZE;
    map->__map_size = 0;
    map->conflict = 0;
    map->puts = 0;
}

size_t map_size(map *map)
{
    assert(map != NULL);
    return map->__map_size;
}

void map_init_custom(map *map, size_t spar, unsigned int (*hashfunc)(char*,int))
{
    assert(map != NULL);
    if(spar < DEFAULT_TABLE_SIZE)
    {
        spar = DEFAULT_TABLE_SIZE;
    }
    map->table = (map_entry**)malloc(spar * sizeof(map_entry*));
    assert(map->table != NULL);
    memset(map->table, 0, spar * sizeof(map_entry*));
    if(hashfunc == NULL)
    {
        hashfunc = hash;
    }
    map->hash = hashfunc;//default elf hash.
    map->table_size = spar;
    map->__map_size = 0;
    map->conflict = 0;
    map->puts = 0;
}

int map_put(map *map, char *key, int key_size, void *value)
{
    assert(map != NULL && key != NULL);
    if(key_size < 0 || value == NULL)
    {
        return OP_MAP_FAIL;
    }
    map_entry *entry = (map_entry*)value;
    entry->next = NULL;//fix seg fault.
    entry->hashcode = map->hash(key, key_size);
    unsigned int pos = entry->hashcode % map->table_size;
    if(map->table[pos] == NULL)//no conflict,directly insert.
    {
        entry->key = key;
        entry->key_size = key_size;
        (map->table)[pos] = entry;
    }
    else
    {
        ++(map->conflict);
        map_entry *temp = NULL;
        map_entry *found = NULL;
        for(temp = (map->table)[pos]; temp != NULL; temp = temp->next)
        {
            found = temp;
            if(temp->hashcode == entry->hashcode && temp->key_size == key_size)
            {
                int is_same = memcmp(temp->key, key, key_size);
                if(is_same == 0)//key already exist.
                {
                    fprintf(stderr,"key: %s already exist!\n", key);
                    return OP_MAP_FAIL;
                }
            }
        }
        entry->key = key;
        entry->key_size = key_size;
        found->next = entry;//insert at tail.
        entry->next = NULL;
    }
    ++(map->__map_size);
    ++(map->puts);
    return OP_MAP_SUCCESS;
}

map_entry *map_get(map *map, char *key, int key_size)
{
    assert(map != NULL && key != NULL);
    if(key_size < 0)
    {
        return NULL;
    }
    map_entry *found = NULL;
    unsigned int hashcode = map->hash(key, key_size);
    unsigned int pos = hashcode % map->table_size;
    map_entry *temp = NULL;
    for(temp = (map->table)[pos]; temp != NULL; temp = temp->next)
    {
        if(temp->hashcode == hashcode && temp->key_size == key_size)
        {
            int is_same = memcmp(temp->key, key, key_size);
            if(is_same == 0)
            {
                found = temp;
                break;
            }
        }
    }
    return found;
}

void map_free_deep(map *map)
{
    assert(map != NULL);
    int i; map_entry *temp = NULL;
    for(i = 0; i < map->table_size; ++i)
    {
        for(temp = map->table[i]; temp != NULL;)
        {
            map_entry *next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(map->table);
    map->table = NULL;
    map->__map_size = 0;
    map->conflict = 0;
    map->puts = 0;
}

void map_clear(map *map)
{
    assert(map != NULL);
    int i; map_entry *temp = NULL;
    for(i = 0; i < map->table_size; ++i)
    {
        for(temp = map->table[i]; temp != NULL;)
        {
            map_entry *next = temp->next;
            temp->next = NULL;//rm ref.
            temp = next;
        }
        map->table[i] = NULL;
    }
    map->__map_size = 0;
    map->conflict = 0;
    map->puts = 0;
}

map_entry *map_remove(map *map, char *key, int key_size)
{
    assert(map != NULL && key != NULL);
    if(key_size < 0 || map->__map_size == 0)
    {
        return NULL;
    }
    map_entry *found = NULL;
    unsigned int hashcode = map->hash(key, key_size);
    unsigned int pos = hashcode % map->table_size;
    map_entry *temp = NULL;
    map_entry *prev = NULL;
    for(temp = (map->table)[pos]; temp != NULL; temp = temp->next)
    {
        if(temp->hashcode == hashcode && temp->key_size == key_size)
        {
            int is_same = memcmp(temp->key, key, key_size);
            if(is_same == 0)
            {
                found = temp;
                break;
            }
        }
        prev = temp;
    }
    if(found != NULL)
    {
        if(prev == NULL)//found is head.
        {
            map_entry *p = found->next;
            found->next = NULL;
            map->table[pos] = p;
        }
        else
        {
            prev->next = found->next;
            found->next = NULL;
        }
        --(map->__map_size);
    }
    return found;
}

void map_free_shallow(map *map)
{
    assert(map != NULL);
    int i; map_entry *temp = NULL;
    for(i = 0; i < map->table_size; ++i)
    {
        for(temp = map->table[i]; temp != NULL;)
        {
            map_entry *next = temp->next;
            temp->next = NULL;//rm ref.
            temp = next;
        }
    }
    free(map->table);
    map->table = NULL;
    map->__map_size = 0;
    map->conflict = 0;
    map->puts = 0;
}
