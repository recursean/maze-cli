#ifndef MAZE_GEN_H
#define MAZE_GEN_H

#define MAZE_ROWS (10)
#define MAZE_COLS (10)

#define TILE_WALLS (4)

#define WALL_NORTH (0)
#define WALL_EAST  (1)
#define WALL_SOUTH (2)
#define WALL_WEST  (3)

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

// Neighbor tile in maze
typedef struct {
    Tile maze[MAZE_ROWS][MAZE_COLS];
    Tile *start_tile;
    Tile *end_tile;
} Maze;

Maze gen_maze_dfs();
void print_maze(Maze *maze);

#endif // MAZE_GEN_H