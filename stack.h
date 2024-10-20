#ifndef STACK_H
#define STACK_H

#include "maze_gen.h"

Tile *pop();
bool push(Tile *tile_to_add);
int size();
bool isEmpty();

#endif // STACK_H