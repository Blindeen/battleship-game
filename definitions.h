#ifndef BATTLESHIP_GAME_DEFINITIONS_H
#define BATTLESHIP_GAME_DEFINITIONS_H

#include <stdbool.h>

enum messages
{
    INPUT_ERROR = -1,
    OK = 0,
    ALLOCATION_ERROR = -4

};

struct ship_t{
    int x;
    int y;
};

struct board_t{
    int width;
    int height;
    char **board;
    unsigned char init:1;
    int ships_amount;
    struct ship_t *ships;
};

int init_board(struct board_t **map, int width, int height); //Function set dimension for board and init flag
bool validate(struct board_t *map); //Check if structure fields are initialized or have proper values
void display_board(struct board_t *map); //Function display whole board
int set_ships(struct board_t *map, int n); //Function set n ships on board

#endif
