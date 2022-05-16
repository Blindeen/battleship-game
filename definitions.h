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

int init_board(struct board_t **map, int width, int height); //Function sets dimension for board and init flag
bool validate(struct board_t *map); //Check if structure fields are initialized or have proper values
void display_board(struct board_t *map); //Function displays whole board
bool is_already(struct board_t *map, int x, int y); //Function checks if ship is already on a map
int set_ships(struct board_t *map, int n); //Function sets n ships on board
int hit_ship(struct board_t *map, int x, int y); //Function returns 1 if some ship was hit or 0 if not and remove ship from map

#endif
