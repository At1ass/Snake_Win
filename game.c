#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

#include <windows.h>

#include "snake_body.h"
#include "field.h"
#include "movement.h"
#include "types.h"

#define SET_POS(a, RC) !((snake_body->a - a) == field->RC - 1 || (snake_body->a - a) == 0) ? snake_body->a - a : field->RC - 1 - snake_body->a;

game_field *field;
Snake *snake_body;

int score = 0;
int speed = 0;

void gen_fruit()
{
    int x;
    int y;
    do
    {
        x = rand() % (field->ROW - 2) + 1;
        y = rand() % (field->COL - 2) + 1;

    }
    while(field->area[x][y] == 'B' || field->area[x][y] == 'o');

    field->area[x][y] = 'A';
}

void game_over()
{

    system("cls");
    printf("YOU FAILED\nYou Score: %d\n", score);
    game_field_cleanup(&field);
    cleanup_snake_body(&snake_body);

    exit(EXIT_SUCCESS);

}

bool revert = false;
void move_snake(int x, int y)
{
    int tmp_X = snake_body->x;
    int tmp_Y = snake_body->y;

    snake_body->x = SET_POS(x, ROW);
    snake_body->y = SET_POS(y, COL);

    if((field->area[snake_body->x][snake_body->y] == 'o'))
    {
        if( snake_body->next->x == snake_body->x || snake_body->next->y == snake_body->y ) {
            snake_body->x = tmp_X;
            snake_body->y = tmp_Y;

            revert = true;
            return; //to move;
        }
        else {
            game_over();
        }
    }

    if(field->area[snake_body->x][snake_body->y] == 'A')
    {
        //++score;
        __asm
        (
            "mov eax, score \n\
            inc eax \n\
            mov score, eax \n"
        );

        add_tail(&snake_body);
        gen_fruit();
    }
    field->area[snake_body->x][snake_body->y] = 'B';

    Snake *tmp = snake_body->next;
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

void Draw()
{
    field->field_ops_t->draw_game_field(&field);
    printf("\nSCORE: %d\n", score);
    printf("SPEED: %d\n", speed / 15);
}

void speed_change()
{
    static bool is_changed = false;

    if(score % 10 == 0 && !is_changed) {
        speed += 15;
        is_changed = true;
    }
    else if (score % 10 != 0) {
        is_changed = true;
    }
}


int main()
{

    int xW = 15, yW = 15;
    int x = -1, y = 0;

    field = init_field();
    field->field_ops_t->init_game_field_size(&field, xW, yW);
    field->field_ops_t->generate_game_area(&field);

    snake_body = init_snake_body();

    while(1){

        //Draw();
        __asm
        (
            "call Draw"
        );

        Sleep(100 - speed);

        int input = -1;
        if(_kbhit())
            input = _getch();
        if(input == 119)
        {
            MOVE_UP
        }
        if(input == 115)
        {
            MOVE_DOWN
        }
        if(input == 97)
        {
            MOVE_LEFT
        }
        if(input == 100)
        {
            MOVE_RIGHT
        }

        move_snake(x, y);

        if(revert) {
            x *= -1;
            y *= -1;
            revert = false;
        }

    }

    game_field_cleanup(&field);
    cleanup_snake_body(&snake_body);
    _getch();

    return 0;
}
