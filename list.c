#include "list.h"
void list_init(list *list)
{
    assert(list != NULL);
    list->head = NULL;
    list->tail = NULL;
    list->__list_size = 0;
    list->inited = 1;
}

void list_free_shalow(list *list)
{
    assert(list != NULL);
    list_item *temp = NULL;
    for(temp = list->head; temp != NULL;)
    {
        list_item *next = temp->next;
        temp->prev = NULL;
        temp->next = NULL;
        temp = next;
    }
    list->inited = 0;
    list->tail = NULL;
    list->head = NULL;
    list->__list_size = 0;
}

void list_free_deep(list *list)
{
    assert(list != NULL);
    list_item *temp = NULL;
    for(temp = list->head; temp != NULL;)
    {
        list_item *next = temp->next;
        free((void*)temp);
        temp = next;
    }
    list->inited = 0;
    list->tail = NULL;
    list->head = NULL;
    list->__list_size = 0;
}

size_t list_size(list *list)
{
    assert(list != NULL && list->inited == 1);
    return list->__list_size;
}

int list_push_back(list *list, void *item)
{
    assert(list != NULL && list->inited == 1);
    if(item == NULL)
    {
        fprintf(stderr,"list insert item is null!\n");
        return OP_LIST_FAIL;
    }
    list_item *__item = (list_item*)item;
    if(list->head == NULL)
    {
        list->head = __item;
        list->tail = __item;
    }
    else
    {
        list->tail->next = __item;
        __item->prev = list->tail;
        __item->next = NULL;
        list->tail = __item;
    }
    ++(list->__list_size);
    return OP_LIST_SUCCESS;
}

int list_insert_before(list *list, int index, void *item)
{
    assert(list != NULL && list->inited == 1);
    if(item == NULL)
    {
        fprintf(stderr,"list insert item is null!\n");
        return OP_LIST_FAIL;
    }
    list_item *target = list_find_by_index(list, index);
    if(target == NULL)
    {
        fprintf(stderr,"list insert target index out of bound!\n");
        return OP_LIST_FAIL;//index out of bound.
    }

    list_item *p = (list_item*)item;
    if(target->prev == NULL)
    {
        p->next = target;
        target->prev = p;
        p->prev = NULL;
        list->head = p;
       //insert before head.
    }
    else
    {
        target->prev->next = p;
        p->prev = target->prev;
        p->next = target;
        target->prev = p;
        //insert normal.
    }
    ++(list->__list_size);
    return OP_LIST_SUCCESS;
}

list_item *list_remove_last(list *list)
{
    assert(list != NULL && list->inited == 1);
    if(list->__list_size == 0){ return NULL;}
    list_item *tail = list->tail;
    list->tail = tail->prev;
    if(tail->prev != NULL)
    {
        tail->prev->next = NULL;
        tail->prev = NULL;
    }
    --(list->__list_size);
    if(list->__list_size == 0){list->head = NULL; list->tail = NULL;}
    return tail;
}

list_item *list_remove_first(list *list)
{
    assert(list != NULL && list->inited == 1);
    if(list->__list_size == 0)
    {
        return NULL;
    }
    else if(list->__list_size == 1)
    {
        return list_remove_last(list);
    }
    else
    {
        list_item *head = list->head;
        list->head = head->next;
        if(head->next != NULL)
        {
            head->next->prev = NULL;
            head->next = NULL;
        }
        --(list->__list_size);
        return head;
    }
}

list_item *list_remove_by_index(list *list, int index)
{
    assert(list != NULL && list->inited == 1);
    if(list->__list_size == 0 || index >= list->__list_size || index < 0)
    {
        return NULL;
    }
    if(index == 0)/*remove head*/
    {
        return list_remove_first(list);
    }
    if(index == list->__list_size - 1)/*remove tail*/
    {
        return list_remove_last(list);
    }
    list_item *rm = list_find_by_index(list, index);
    rm->prev->next = rm->next;
    rm->next->prev = rm->prev;
    rm->prev = NULL;
    rm->next = NULL;
    
    --(list->__list_size);
    return rm;
}

list_item *list_find_by_index(list *list, int index)
{
    assert(list != NULL && list->inited == 1);
    int i;
    list_item *target = list->head;
    if(list->__list_size == 0 ||
       target == NULL ||
       index > list->__list_size)
    {
        return NULL;
    }

    for(i = 0; i < list->__list_size; ++i)
    {
        if(i < index){target = target->next;}
        else{break;}
    }
    return target;
}
