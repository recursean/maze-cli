#ifndef MAZE_DRAW_H
#define MAZE_DRAW_H

#include "maze.h"

#define PLAYER_CUSHION (3)

void draw_player(Player *player);
void draw_walls(Maze *maze, Player *player);
void draw_maze(Maze *maze, Player *player);

#endif // MAZE_DRAW_H