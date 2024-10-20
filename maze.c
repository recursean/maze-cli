#include <ncurses.h>
#include "ncurses_funcs.h"
#include "maze_gen.h"

#define HELP_DELAY 50000
#define TITLE_BORDER_DELAY 5000

static void init_ncurses();
static void display_title();
static void print_title_border();
static void play_maze();

int main() {
    init_ncurses();
    display_title();

    int ch;
    while((ch = getch()) != 'q') {
        switch(ch) { 
            case 's':
                clear();
                gen_maze_dfs();
                print_maze();
                play_maze();
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

    print_title_border();
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

static void play_maze() {
    int ch;
    int x = 0, y = 0;
    char *player = "^";

    // move cursor to coords (y, x) and print player
    mvprintw(y, x, player);
    refresh();

    while ((ch = getch()) != 'q') {
        mvprintw(y, x, " "); // Erase the character
        switch (ch) {
            case KEY_UP:    
                y--; 
                player = "^";
                break;
            case KEY_DOWN:  
                y++; 
                player = "v";
                break;
            case KEY_LEFT:  
                x--;
                player = "<"; 
                break;
            case KEY_RIGHT: 
                x++; 
                player = ">";
                break;
        }
        mvprintw(y, x, player); // Draw the character
        refresh();
    }
}