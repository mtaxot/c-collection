#include<stdio.h>
#include"array.h"
typedef struct _stud
{
    AS_ARRAY_ITEM;
    int id;
    char *name;
    int score;
}stud_t;


int main(int argc, char **argv)
{
    array aarray;
    array_init(&aarray);

    stud_t stud0;
    stud0.id = 0;
    stud0.name = "0-stud";
    stud0.score = 90;

    stud_t stud1;
    stud1.id = 1;
    stud1.name = "1-stud";
    stud1.score = 30;

    stud_t stud2;
    stud2.id = 2;
    stud2.name = "2-stud";
    stud2.score = 20;

    stud_t stud3;
    stud3.id = 3;
    stud3.name = "3-stud";
    stud3.score = 30;

    stud_t stud4;
    stud4.id = 4;
    stud4.name = "4-stud";
    stud4.score = 40;

    array_push_back(&aarray, &stud0);
    array_push_back(&aarray, &stud1);
    array_push_back(&aarray, &stud2);
    array_push_back(&aarray, &stud3);

    array_insert_before(&aarray, 4, &stud4);

    array_item *item = NULL;
    printf("array size = %ld\n", get_array_size(&aarray));

    int from = 0;
    array_for_each(&aarray, item, from)
    {
        stud_t *temp = (stud_t *)item;
        if(temp != NULL)
        {
            printf("array_get: id=%d, name=%s, score=%d\n",temp->id, temp->name, temp->score);
        }
    }

    printf("array_find_by_index:6\n");
    item = array_find_by_index(&aarray, 6);
    if(item != NULL)
    {
        stud_t *temp = (stud_t *)item;
        printf("array_get: id=%d, name=%s, score=%d\n",temp->id, temp->name, temp->score);
    }
    return 0;
}
















