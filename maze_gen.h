#ifndef MAZE_GEN_H
#define MAZE_GEN_H

#include "maze.h"

// Neighbor tile in maze
typedef struct {
    int tile_wall;
    Tile *tile;
} Neighbor;

Maze gen_maze_dfs();
void print_maze(Maze *maze);

#endif // MAZE_GEN_H