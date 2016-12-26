#include "list.h"

#include<stdio.h>

typedef struct sutd
{
    AS_LIST_ITEM;
    int id;
    char *name;
}stud_t;



int main(int argc, char **argv)
{
    list list1;
    int ret = 0;
    list_init(&list1);

    stud_t stud1;
    stud1.id = 0;
    stud1.name = "0-stu";

    stud_t stud2;
    stud2.id = 1;
    stud2.name = "1-stu";

    stud_t stud3;
    stud3.id = 2;
    stud3.name = "2-stu";

    stud_t stud4;
    stud4.id = 3;
    stud4.name = "3-stu";

    ret = list_push_back(&list1, &stud1);
    if(ret == OP_LIST_FAIL) return -1;

    ret = list_push_back(&list1, &stud2);
    if(ret == OP_LIST_FAIL) return -1;

    ret = list_push_back(&list1, &stud3);
    if(ret == OP_LIST_FAIL) return -1;

    //ret = list_push_back(&list, stud4);
    //if(ret == OP_LIST_FAIL) return -1;  

    list_insert_before(&list1, 3, &stud4);

    list_item *temp = NULL;
    list_for_each(&list1, temp)
    {
	stud_t *p = (stud_t*)temp;
        printf("id=%d, name=%s\n",p->id, p->name);
    }

    list_free_shalow(&list1);
    return 0;
}
