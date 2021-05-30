#include "snake_body.h"

#define SET_POS(a, RC) !((self->a - a) == field->RC - 1 || (self->a - a) == 0) ? self->a - a : field->RC - 1 - self->a;

void add_tail_t(Snake **snake_body)
{
        if((*snake_body) == NULL) {
                (*snake_body) = (Snake *)malloc(sizeof(Snake));
                (*snake_body)->x = 4;
                (*snake_body)->y = 4;
                (*snake_body)->next = NULL;
                return;
        }

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

void move_snake_t(Snake *self, game_field *field, int x, int y, bool *revert)
{
    int tmp_X = self->x;
    int tmp_Y = self->y;

    self->x = SET_POS(x, ROW);
    self->y = SET_POS(y, COL);

    if((field->area[self->x][self->y] == 'o'))
    {
        if( self->next->x == self->x && self->next->y == self->y ) {
            self->x = tmp_X;
            self->y = tmp_Y;

            *revert = true;
            return; //to move;
        }
        else {
            exit(EXIT_SUCCESS);
        }
    }

    if(field->area[self->x][self->y] == 'A')
    {
        //++score;
        __asm
        (
            "mov eax, score \n\
            inc eax \n\
            mov score, eax \n"
        );

        self->add_tail(&self);
        field->field_ops_t->generate_fruit(&field);
    }
    field->area[self->x][self->y] = 'B';

    Snake *tmp = self->next;
    while(tmp != NULL)
    {
        int tx = tmp->x;
        int ty = tmp->y;

        tmp->x = tmp_X;
        tmp->y = tmp_Y;

        field->area[tmp->x][tmp->y] = 'o';

        tmp_X = tx;
        tmp_Y = ty;

        tmp = tmp->next;
    }

    field->area[tmp_X][tmp_Y] = ' ';
}

Snake *init_snake_body()
{
    Snake* snake_body = NULL;

    for(int i = 0; i < 3; ++i)
        add_tail_t(&snake_body);

    snake_body->add_tail = &add_tail_t;
    snake_body->move_snake = &move_snake_t;

    return snake_body;
}

void cleanup_snake_body(Snake **snake_body)
{

    while(*snake_body)
    {
        Snake *tmp = (*snake_body)->next;

        free(*snake_body);

        *snake_body = tmp;
    }
}
