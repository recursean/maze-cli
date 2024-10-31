#include <stdbool.h>
#include <ncurses.h>
#include "ncurses_funcs.h"
#include "maze.h"
#include "maze_gen.h"
#include "maze_draw.h"

#define HELP_DELAY 50000
#define TITLE_BORDER_DELAY 5000

static void init_ncurses();
static void display_title();
static void print_title_border();
static void play_maze(Maze *maze);

int main() {
    Maze maze = gen_maze_dfs();
    init_ncurses();
    display_title();

    int ch;
    while((ch = getch()) != 'q') {
        switch(ch) { 
            case 's':
                clear();
                print_maze(&maze);
                play_maze(&maze);
                break;
            default:
                continue;
        }
    }
    
    endwin();
    return 0;
}

static void init_ncurses() {
    initscr();
    
    // allow for arrow key input
    keypad(stdscr, TRUE);

    // read in user input as soon as entered
    cbreak();

    // dont echo user input to console
    noecho();
}

static void display_title() {
    char *title = "Maze";
    int title_delay = 500000;

    initscr();
    noecho();

    print_center(title, title_delay, 0, 1);

    char *help_msg1 = "s-start";
    char *help_msg2 = "q-quit";
    print_center(help_msg1, HELP_DELAY, 3, 1); 
    print_center(help_msg2, HELP_DELAY, 4, 1); 

    // print_title_border();
}

static void print_title_border() {
    int row, col, x, y;
    getmaxyx(stdscr, row, col);

    char* border_char = "#";

    x = 0;
    for(y = 0; y < col; y++) {
        print_delay(border_char, TITLE_BORDER_DELAY, x, y);
    }
    for(x = 1; x < row; x++) {
        print_delay(border_char, TITLE_BORDER_DELAY, x, y);
    }
    for(y = y-1; y < 0; y--) {
        print_delay(border_char, TITLE_BORDER_DELAY, x, y);
    }
    for(x = x-1; x < 0; x--) {
        print_delay(border_char, TITLE_BORDER_DELAY, x, y);
    }
}

static void play_maze(Maze *maze) {
    int ch;
    Player player = {0};
    player.curr_tile = maze->start_tile;

    // draw player and walls on screen
    draw_maze(maze, &player);
    refresh();

    // exit maze when user presses q
    bool exit = false;

    while ((ch = getch()) != 'q') {
        // erase old player position 
        mvaddch(player.curr_tile->y, player.curr_tile->x, ' ');
        switch (ch) {
            case KEY_UP:    
                player.curr_tile->y--; 
                break;
            case KEY_DOWN:  
                player.curr_tile->y++; 
                break;
            case KEY_LEFT:  
                player.curr_tile->x--;
                break;
            case KEY_RIGHT: 
                player.curr_tile->x++; 
                break;
            case 'q': 
                exit = true; 
                break;
        }

        // user requested exit
        if(exit) {
            break;
        }

        // draw updated player
        draw_maze(maze, &player);

        // draw player
        // mvaddch(player.curr_tile->y, player.curr_tile->x, PLAYER_CHAR);
        refresh();
    }
}