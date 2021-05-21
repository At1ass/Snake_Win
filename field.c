#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

#include <emmintrin.h>

#include "field.h"

void generate_game_area_t(game_field **self)
{
    (*self)->area = (char **)malloc((*self)->ROW * sizeof(char *));
    (*self)->old_area = (char **)malloc((*self)->ROW * sizeof(char *));
    for(int i = 0; i < (*self)->ROW; ++i) {
        (*self)->area[i] = (char *)malloc((*self)->COL * sizeof(char));
        (*self)->old_area[i] = (char *)malloc((*self)->COL * sizeof(char));
    }

    for(int i = 0; i < (*self)->ROW; ++i) {
        for(int j = 0; j < (*self)->COL; ++j) {
            if(i == 0 || j == 0 || i == (*self)->ROW - 1 || j == (*self)->COL - 1) {
                (*self)->area[i][j] = '0';
                (*self)->old_area[i][j] = '0';
            }
            else {
                (*self)->area[i][j] = ' ';
                (*self)->old_area[i][j] = ' ';
            }
        }
    }



    (*self)->area[4][4] = 'B';
    (*self)->old_area[4][4] = 'B';
    (*self)->area[(*self)->ROW / 2 + 1][(*self)->COL / 2 + 1] = 'A';
    (*self)->old_area[(*self)->ROW / 2 + 1][(*self)->COL / 2 + 1] = 'A';

    for(int i = 0; i < (*self)->ROW; ++i) {
        fwrite((*self)->area[i], sizeof(char), (*self)->COL, stdout);
        fwrite("\n", sizeof(char), 1, stdout );
    }
}
void init_game_field_size_t(game_field **self, int x, int y)
{
    (*self)->ROW = y;
    (*self)->COL = x;
}

game_field * init_field()
{
    game_field * field = (game_field *)calloc(1, sizeof(game_field));
    field->field_ops_t = (game_field_ops *)calloc(1, sizeof(game_field_ops));

    field->field_ops_t->init_game_field_size = &init_game_field_size_t;
    field->field_ops_t->generate_game_area = &generate_game_area_t;
    field->field_ops_t->draw_game_field = &draw_game_field_t;

    return field;
}

void draw_game_field_t(game_field **self)
{
    COORD pos;
    HANDLE h_stdout = GetStdHandle(STD_OUTPUT_HANDLE);

    pos.X = 0;
    pos.Y = 0;
    for(int i = 0; i < (*self)->ROW; ++i) {

        if((0xFFFFFFFF & ~_mm_movemask_epi8(_mm_cmpeq_epi8(
                          _mm_load_si128((__m128i const *)(*self)->area[i]),
                          _mm_load_si128((__m128i const *)(*self)->old_area[i])))))
        {
            pos.Y = i;
            SetConsoleCursorPosition(h_stdout, pos);
            fwrite((void *)(*self)->area[i], sizeof(char), (*self)->COL, stdout);

            _mm_store_si128((__m128i *)(*self)->old_area[i],
                            _mm_load_si128((__m128i const *)(*self)->old_area[i]));
        }

    }

}

void game_field_cleanup(game_field **self)
{
    free((*self)->field_ops_t);
    free((*self));
}

