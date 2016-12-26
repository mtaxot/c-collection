/*
 * A list template, linkedlist, 2 direction.
 *
 * @author ZhangShiming
 */
#ifndef __LIST_H_
#define __LIST_H_
#include<stdio.h>
#include<assert.h>
#include<stdlib.h>

/* base list "class" for child to "extend" 
 * ,however some compilers implment it not as first addr.
 */
#define AS_LIST_ITEM list_item __list_item

#define OP_LIST_SUCCESS (1)
#define OP_LIST_FAIL (-1)

typedef struct _list_item
{
    struct _list_item *prev;
    struct _list_item *next;
}list_item;

typedef struct _list
{
    size_t __list_size;
    list_item *head;
    list_item *tail;
    unsigned char inited;
    //int (*list_init)(struct _list *list);
}list;

#define list_for_each(__plist__, plist_item) \
            for(plist_item = (__plist__)->head;\
                        plist_item != NULL;\
                             plist_item = plist_item->next)

void list_init(list *list);//init empty linkedlist.

void list_free_shalow(list *list);//destroy linkedlist. member is stack mem.

void list_free_deep(list *list);//destroy linkedlist. member is heap mem.

size_t list_size(list *list);//return list's size.

int list_push_back(list *list, void *item);//insert item at tail.

int list_insert_before(list *list, int index, void *item);//insert before index.

list_item *list_remove_last(list *list);//rm tail item of list.

list_item *list_remove_first(list *list);//rm head item of list.

list_item *list_remove_by_index(list *list, int index);// remove by index.

list_item *list_find_by_index(list *list, int index); // find by index.
#endif

