#include <ncurses.h>
#include <string.h>
#include <unistd.h>

#define MAX_DELIM_SPACES (5)

/**
 * Print message in center of screen.
 * 
 * Specified message will be output at the center of the
 * screen, meaning the middle of the message will appear
 * in the center. A delay can be added between characters
 * printed.
 * 
 * @param message String to be output in the center of screen
 * @param delay_microsec Microseconds to delay between each char 
 * @param y_offset Offset of middle x coord to print. Useful for multi line msgs.
 * @param num_delim_spaces Number of spaces to put between characters. Max 5.
 */
void print_center(char *message, int delay_microsec, int x_offset, int num_delim_spaces) {
    int row, col, x, y;
    
    getmaxyx(stdscr, row, col);

    // position in center of screen
    x = row / 2 + x_offset;
    y = (col - ( strlen(message) * (num_delim_spaces + 1) ) ); 
    y = y < 0 ? 0 : y / 2;    

    // build space string separator
    char space_delim[MAX_DELIM_SPACES];
    if(num_delim_spaces > 0 && num_delim_spaces <= MAX_DELIM_SPACES) {
        int i = 0;
        for(; i < num_delim_spaces; i++) {
            space_delim[i] = ' ';
        }
        // add trailing null
        if(i < MAX_DELIM_SPACES) {
            space_delim[i] = '\0';
        }
    } 

    if(has_colors()) {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(1));
    }

    // print message
    for(int i = 0; i < strlen(message); i++) {
        mvaddch(x, y++, message[i] | A_BOLD | A_UNDERLINE | A_ITALIC);
        if(num_delim_spaces > 0) {
            mvprintw(x, y, "%s", space_delim);
            y += num_delim_spaces;
        }
        refresh();
        usleep(delay_microsec);
    }

    attroff(COLOR_PAIR(1));
}

void print_delay(char *message, int delay_microsec, int x, int y) {
    for(int i = 0; i < strlen(message); i++) {
        mvaddch(x, y, message[i]);
        refresh();
        usleep(delay_microsec);
    }
}