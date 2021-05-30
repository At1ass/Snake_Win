#ifndef __SNAKE_BODY_H__
#define __SNAKE_BODY_H__

#include <stdlib.h>
#include <stddef.h>
#include "field.h"
#include "types.h"

struct snake
{
        int x;
        int y;

        struct snake *next;

        void (*add_tail)(struct snake **);
        void (*move_snake)(struct snake *, game_field *, int, int, bool *);
};
typedef struct snake Snake;

Snake * init_snake_body();

void cleanup_snake_body(Snake** snake_body);

//void add_tail_t(Snake **snake_body);

#endif
