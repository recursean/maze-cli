#include <ncurses.h>
#include "ncurses_funcs.h"

static void init_ncurses();
static void display_title();
static void play_maze();

int main() {
    init_ncurses();
    display_title();

    int ch;
    while((ch = getch()) != 'q') {
        switch(ch) { 
            case 's':
                clear();
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
    int help_delay = 50000;
    print_center(help_msg1, help_delay, 3, 1); 
    print_center(help_msg2, help_delay, 4, 1); 
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