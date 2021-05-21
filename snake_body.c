#include "snake_body.h"

void add_tail(Snake **snake_body)
{
        if((*snake_body) == NULL) {
                (*snake_body) = (Snake *)malloc(sizeof(Snake));
                (*snake_body)->x = 4;
                (*snake_body)->y = 4;
                (*snake_body)->next = NULL;
                return;
        }


        static int i = 0;
        Snake *tmp = (*snake_body);
        while(tmp->next != NULL){
                tmp = tmp->next;
        }
        Snake *ttmp = (Snake *)malloc(sizeof(Snake));
        ttmp->x = tmp->x;
        ttmp->y = tmp->y;
        ttmp->next = NULL;
        tmp->next = ttmp;
}

Snake *init_snake_body()
{
    Snake* snake_body = NULL;

    for(int i = 0; i < 3; ++i)
        add_tail(&snake_body);

    return snake_body;
}

void cleanup_snake_body(Snake **snake_body)
{

    while(snake_body)
    {
        Snake *tmp = (*snake_body)->next;

        free(snake_body);

        snake_body = tmp;
    }
}
