#ifndef MAZE_H
#define MAZE_H

#define MAZE_ROWS (10)
#define MAZE_COLS (10)

#define TILE_WALLS (4)

#define WALL_NORTH (0)
#define WALL_EAST  (1)
#define WALL_SOUTH (2)
#define WALL_WEST  (3)

#define PLAYER_CHAR '*'

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
    Tile maze[MAZE_ROWS][MAZE_COLS];
    Tile *start_tile;
    Tile *end_tile;
} Maze;

typedef struct {
    Tile *curr_tile;
} Player;

#endif // MAZE_H