#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"

#define STACK_SIZE (5000)

Tile *tile_stack[STACK_SIZE];
int used_size = 0;

/**
 * Pop element off stack.
 * 
 * @return Last element that was pushed onto stack or NULL.
 */
Tile *pop() {
    if(used_size > 0) {
        return tile_stack[used_size--];
    }
    else {
        return NULL;
    }
}

/**
 * Push element onto top of stack.
 * 
 * @return true if element was added, false if no space left
 */
bool push(Tile *tile_to_add) {
    if(used_size < STACK_SIZE) {
        tile_stack[used_size++] = tile_to_add;
        return true;
    }
    else {
        return false;
    }
}

/**
 * Get current used size of stack.
 * 
 * @return Current used size of stack
 */
int size() {
    return used_size;
}

/**
 * Determine if stack is empty or not.
 * 
 * @return true if no elements are in stack, false otherwise
 */
bool isEmpty() {
    return used_size == 0;
}