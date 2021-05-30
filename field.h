#ifndef __FIELD_H__
#define __FIELD_H__

#include <stdlib.h>

typedef struct field_ops game_field_ops;
typedef struct field_t game_field;

struct field_t
{
    char ** area;
    char ** old_area;

    int ROW;
    int COL;

    game_field_ops *field_ops_t;

};

struct field_ops
{
    void (*init_game_field_size)(game_field **, int, int);
    void (*generate_game_area)(game_field **);
    void (*draw_game_field)(game_field **);
    void (*generate_fruit)(game_field **);
};

game_field * init_field();

void game_field_cleanup(game_field **self);

#endif
