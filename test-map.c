#include "map.h"
#include <stdio.h>

typedef struct _stud
{
    AS_MAP_ENTRY;
    int id;
    char *name;
    int score;
}stud_t;


int main(int argc, char **argv)
{
    map amap;
    map_init(&amap);

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

    map_put(&amap, stud0.name, strlen(stud0.name), &stud0);
    map_put(&amap, stud1.name, strlen(stud1.name), &stud1);
    map_put(&amap, stud2.name, strlen(stud2.name), &stud2);
    map_put(&amap, stud3.name, strlen(stud3.name), &stud3);

    printf("map size = %ld\n", map_size(&amap));

    stud_t *temp = (stud_t*)map_get(&amap, "1-stud", strlen("1-stud"));
    if(temp != NULL)
    {
        printf("map_get: id=%d, name=%s, score=%d\n",temp->id, temp->name, temp->score);
    }

    map_entry *temp1 = NULL;
    int i;
    printf("map for each:\n");
    map_for_each(&amap,temp1, i)
    {
        stud_t *studx = (stud_t*)temp1;
        printf("id=%d, name=%s, score=%d\n",studx->id, studx->name, studx->score);
    }
    printf("map remove:%s\n","3-stud");
    map_remove(&amap, "3-stud", strlen("3-stud"));
    printf("map size = %ld\n", map_size(&amap));
    printf("map for each:\n");
    map_for_each(&amap,temp1, i)
    {
        stud_t *studx = (stud_t*)temp1;
        printf("id=%d, name=%s, score=%d\n",studx->id, studx->name, studx->score);
    }
    printf("map clear:\n");
    map_clear(&amap);
    printf("map for each:\n");
    map_for_each(&amap,temp1, i)
    {
        stud_t *studx = (stud_t*)temp1;
        printf("id=%d, name=%s, score=%d\n",studx->id, studx->name, studx->score);
    }
    printf("map size = %ld\n", map_size(&amap));
    map_free_shallow(&amap);
    return 0;
}
