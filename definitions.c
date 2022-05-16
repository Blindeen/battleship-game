#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
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
    //Input validation
    if(validate(map))
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

bool is_already(struct board_t *map, int x, int y)
{
    //Condition which checks if ship is set on x y position
    if(*(*(map->board+y)+x) == 'S')
    {
        return true;
    }

    return false;
}

int set_ships(struct board_t *map, int n)
{
    //Input validation
    if(!validate(map) || n <= 0)
    {
        return INPUT_ERROR;
    }

    //Allocation of n ship_t structures
    struct ship_t *ships = (struct ship_t *) calloc(n, sizeof(struct ship_t));
    if(ships == NULL)
    {
        return ALLOCATION_ERROR;
    }

    //Assignment of each ship position and setting up ships on board
    srand(time(NULL));
    int x, y;
    for(int i = 0; i < n; ++i)
    {
        x = rand()%map->width;
        y = rand()%map->height;
        while(is_already(map, x, y))
        {
            x = rand()%map->width;
            y = rand()%map->height;
        }
        (*(ships+i)).x = x;
        (*(ships+i)).y = y;
        *(*(map->board+y)+x) = 'S';
    }

    //Assignment of structure fields
    map->ships_amount = n;
    map->ships = ships;

    return OK;
}

int hit_ship(struct board_t *map, int x, int y)
{
    //Input validation
    if(!validate(map) || x < 0 || y < 0 || x > map->width-1 || y > map->height-1)
    {
        return INPUT_ERROR;
    }

    //Checking if ship is placed on x y position
    if((*(*(map->board+y)+x)) == 'S')
    {
        *(*(map->board+y)+x) = 'X';
        return 1; //Ship is place on x y position
    }

    return 0; //Ship is not placed on x y position
}