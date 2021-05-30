#include <windows.h>
#include <stdio.h>
#include <conio.h>

#include "menu.h"
#include "types.h"

bool is_start = true;

#define POS_START 3
#define POS_INSTR 8
#define REMOVE

void draw_menu()
{
    system("cls");
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD pos;
    pos.X = 3;
    pos.Y = POS_START;

    SetConsoleCursorPosition(hStdOut, pos);

    printf("START GAME");

    pos.Y = POS_INSTR;

    SetConsoleCursorPosition(hStdOut, pos);
    printf("INSTRUCTION");

    pos.X = 1;
    pos.Y = POS_START;
    SetConsoleCursorPosition(hStdOut, pos);
    printf(">>");
}

void redraw()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD pos;
    pos.X = 1;

    if(is_start) {
        pos.Y = POS_START;
        SetConsoleCursorPosition(hStdOut, pos);
        printf("  ");
        is_start = false;
        pos.Y = POS_INSTR;

    }
    else {
        pos.Y = POS_INSTR;
        SetConsoleCursorPosition(hStdOut, pos);
        printf("  ");
        is_start = true;
        pos.Y = POS_START;

    }

    SetConsoleCursorPosition(hStdOut, pos);
    printf(">>");
}

void show_instruction()
{
    system("cls");


    printf("You need take 10\nfruits for win\nFor gaming you need\nEN locale in your\nkeyboard\n\n");
    printf("WASD - moving\n\n");
    printf("A - close this menu\n");

    int input = -1;
    while (1) {
        input = _getch();

        if(input == 97)
            return;
    }

}

void start_menu()
{
    draw_menu();

    int input = -1;
    while (1) {
        input = _getch();

        if(input == 115 || input == 119)
            redraw();

        if(input == 100)
        {
            if(is_start) {
                system("cls");
                return;
            }
            else
            {
                show_instruction();
                draw_menu();
                redraw();
            }
        }
    }
}
