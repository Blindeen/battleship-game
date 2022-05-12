#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "definitions.h"

int init_board(struct board_t **map, int width, int height)
{
    if(map == NULL || width <= 0 || height <= 0)
    {
        return INPUT_ERROR;
    }

    //Allocation of board structure
    struct board_t *board = (struct board_t *) calloc(1, sizeof(struct board_t));
    if(board == NULL)
    {
        return ALLOCATION_ERROR;
    }

    //Allocation of board
    char **sheet = (char **) calloc(height, sizeof(char *));
    if(sheet == NULL)
    {
        free(board);
        return ALLOCATION_ERROR;
    }

    for(int i = 0; i < height; ++i)
    {
        //Allocation of row
        *(sheet+i) = (char *) calloc(width, sizeof(char));
        if(*(sheet+i) == NULL)
        {
            for(int j = 0; j < i; ++j)
            {
                free(*(sheet+j));
            }
            free(sheet);
            free(board);
            return ALLOCATION_ERROR;
        }

        //Filling a row
        for(int j = 0; j < width; ++j)
        {
            *(*(sheet+i)+j) = '~';
        }
    }

    //Assignment of structure fields
    board->width = width;
    board->height = height;
    board->init = 1;
    board->board = sheet;

    *map = board;

    return OK;
}

bool validate(struct board_t *map)
{
    if(map == NULL || map->board == NULL || map->height <=0 || map->width <= 0 || map->init == 0)
    {
        return false;
    }

    return true;
}

void display_board(struct board_t *map)
{
    if(validate(map) == true)
    {
        for(int i = 0; i < map->height; ++i)
        {
            for(int j = 0; j < map->width; ++j)
            {
                printf("%c ", *(*(map->board+i)+j));
            }
            printf("\n");
        }
    }
}