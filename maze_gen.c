#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "maze_gen.h"
#include "stack.h"

#define MAZE_ROWS (10)
#define MAZE_COLS (10)

#define TILE_WALLS (4)

#define WALL_NORTH (0)
#define WALL_EAST  (1)
#define WALL_SOUTH (2)
#define WALL_WEST  (3)

static int opposite_wall(int wall);
static Neighbor get_random_neighbor(Tile *curr_tile);

Tile maze[MAZE_ROWS][MAZE_COLS];

/**
 * Generate 2D maze using DFS.
 */
void gen_maze_dfs() {
    // seed random number generator with current time
    srand(time(0));

    // init walls on all sides for all tiles to be true
    for(int i = 0; i < MAZE_ROWS; i++) {
        for(int j = 0; j < MAZE_COLS; j++) {
            maze[i][j].visited = false;
            maze[i][j].x = i;
            maze[i][j].y = j;
            for(int k = 0; k < TILE_WALLS; k++) {
                maze[i][j].walls[k] = true;
            }
        }
    }

    // start at random tile
    int curr_row = rand() % MAZE_ROWS;
    int curr_col = rand() % MAZE_COLS;
    Tile *curr_tile = &maze[curr_row][curr_col];

    // push current tile onto stack
    push(curr_tile);

    // loop 
    while(!isEmpty()) {
        // mark current tile as visited
        curr_tile->visited = true;

        // choose random neighbor tile
        Neighbor rand_neighbor = {0};
        rand_neighbor = get_random_neighbor(curr_tile);

        // remove wall between current and neighbor tile
        if(rand_neighbor.tile_wall != -1) {
            curr_tile->walls[rand_neighbor.tile_wall] = false;
        }
        else {
            // pop from stack and iterate again
            curr_tile = pop(); 
            continue;
        }

        // remove wall between neighbor and current tile
        rand_neighbor.tile->walls[opposite_wall(rand_neighbor.tile_wall)] = false;

        // push current tile onto stack
        push(curr_tile);

        // prepare for next iteration
        curr_tile = rand_neighbor.tile;
    }
}

void print_maze() {

}

/**
 * Returns the wall opposite of specified wall.
 * 
 * @param wall Current wall to return opposite of
 * @return Opposite wall of specified wall
 */
static int opposite_wall(int wall) {
    if(wall >= 2) {
        return wall - 2;
    }
    return wall + 2;
}

/**
 * Return random unvisited neighbor tile.
 * 
 * Given a starting x,y position, this function will
 * return a random unvisited neighor. Neighbors are
 * 1 tiles to the north, east, south, and west of the
 * current tile.
 * 
 * @param curr_tile Current position in maze
 * @return Neighbor tile
 */
static Neighbor get_random_neighbor(Tile *curr_tile) {
    Neighbor unvisited_neighbors[4];
    int unvisited_neighbors_count = 0;
    Tile *neighbor_tile = NULL;

    for(int i = 0; i < TILE_WALLS; i++) {
        switch(i) {
            case WALL_NORTH:
                if(curr_tile->x - 1 < 0) {
                    continue;
                }
                neighbor_tile = &maze[curr_tile->x - 1][curr_tile->y];
                break;
            case WALL_EAST:
                if(curr_tile->y + 1 >= MAZE_COLS) {
                    continue;
                }
                neighbor_tile = &maze[curr_tile->x][curr_tile->y + 1];
                break;
            case WALL_SOUTH:
                if(curr_tile->x + 1 >= MAZE_ROWS) {
                    continue;
                }
                neighbor_tile = &maze[curr_tile->x + 1][curr_tile->y];
                break;
            case WALL_WEST:
                if(curr_tile->y - 1 < 0) {
                    continue;
                }
                neighbor_tile = &maze[curr_tile->x][curr_tile->y - 1];
                break;
            default:
                break;
        }
        if(neighbor_tile != NULL && !neighbor_tile->visited) {
            Neighbor neighbor;
            neighbor.tile_wall = i;
            neighbor.tile = neighbor_tile;
            unvisited_neighbors[unvisited_neighbors_count++] = neighbor;
            neighbor_tile = NULL;
        }
    }

    if(unvisited_neighbors_count == 0) {
        // all neighbors visited
        Neighbor neighbor;
        neighbor.tile_wall = -1;
        return neighbor;
    }   
    
    // return random unvisited neighbor
    return unvisited_neighbors[rand() % unvisited_neighbors_count];
}