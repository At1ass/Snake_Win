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
#include "menu.h"

game_field *field;
Snake *snake_body;



int score = 0;
int speed = 0;
bool game_state = false;

void init_game()
{
    HANDLE hConsole = GetConsoleWindow();

    RECT rect = {100, 100, 300, 450};

    MoveWindow(hConsole, rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,TRUE);
}

void game_over()
{
    if(!game_state) {
        system("cls");
        printf("YOU FAILED\nYou Score: %d\n\n\n\n\n\n\n\n", score);
        game_field_cleanup(&field);
        cleanup_snake_body(&snake_body);
    }
    else
    {
        system("cls");
        printf("YOU WIN\n\n\n\n\n\n\n\n");
        game_field_cleanup(&field);
        cleanup_snake_body(&snake_body);
    }
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
bool revert = false;
void move(int *x_f, int *y_f)
{
    int x = *x_f;
    int y = *y_f;
    Sleep(150 - speed);

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

    snake_body->move_snake(snake_body, field, x, y, &revert);

    if(revert) {
        x *= -1;
        y *= -1;
        revert = false;
    }

    *x_f = x;
    *y_f = y;
}


int main()
{

    int xW = 15, yW = 15;
    int x = -1, y = 0;

    system("cls");
    init_game();


    start_menu();


    atexit(game_over);

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

        move(&x, &y);

        if(score >= 10)
        {
            game_state = true;
            exit(EXIT_SUCCESS);
        }

    }

    game_field_cleanup(&field);
    cleanup_snake_body(&snake_body);

    return 0;
}
