#ifndef MAZE_GEN_H
#define MAZE_GEN_H

// Single tile in maze
typedef struct {
    // 0 N, 1 E, 2 S, 3 W
    bool walls[4];
    bool visited;
    int x;
    int y;
} Tile;

// Neighbor tile in maze
typedef struct {
    int tile_wall;
    Tile *tile;
} Neighbor;

void gen_maze_dfs();
void print_maze();

#endif // MAZE_GEN_H