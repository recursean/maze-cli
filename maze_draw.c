#include <ncurses.h>
#include "maze_draw.h"

void draw_maze(Maze *maze, Player *player) {
    draw_player(player);
    draw_walls(maze, player);
}

void draw_player(Player *player) {
    // move cursor to coords (y, x) and print player
    mvaddch(player->curr_tile->y, player->curr_tile->x - 1, PLAYER_CHAR);

    // clear player direct surroundings
    for(int y = player->curr_tile->y - PLAYER_CUSHION / 2; y < PLAYER_CUSHION + PLAYER_CUSHION / 2; y++) {
        for(int x = player->curr_tile->x - PLAYER_CUSHION / 2; x < PLAYER_CUSHION + PLAYER_CUSHION / 2; x++) {
            mvaddch(y, x, ' ');
        }
    }
}

void draw_walls(Maze *maze, Player *player) {

}