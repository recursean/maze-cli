#include <ncurses.h>

int main() {
    int x = 0, y = 0;
    int ch;
    char *player = "^";

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

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

    endwin();
    return 0;
}
