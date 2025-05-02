#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct s_grid {
   int grid[4][4];
} t_grid;

void add_new_tile(t_grid *g)
{
    int empty[16];
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (g->grid[i][j] == 0) {
                empty[count++] = i * 4 + j;
            }
        }
    }
    if (count > 0) {
        int k = rand() % count;
        int index = empty[k];
        int i = index / 4;
        int j = index % 4;
        g->grid[i][j] = (rand() % 10 == 0 ? 4 : 2);
    }
}

bool slide_left(int row[4])
{
    int temp[4];
    int count = 0;
    for (int i = 0; i < 4; i++) {
        if (row[i] != 0) {
            temp[count++] = row[i];
        }
    }
    int new_row[4] = {0};
    int pos = 0;
    for (int i = 0; i < count; i++) {
        if (i < count - 1 && temp[i] == temp[i + 1]) {
            new_row[pos] = temp[i] * 2;
            i++;
        } else {
            new_row[pos] = temp[i];
        }
        pos++;
    }
    bool changed = false;
    for (int i = 0; i < 4; i++) {
        if (row[i] != new_row[i]) {
            changed = true;
        }
        row[i] = new_row[i];
    }
    return changed;
}

bool slide_right(int row[4])
{
    for (int i = 0; i < 2; i++) {
        int temp = row[i];
        row[i] = row[3 - i];
        row[3 - i] = temp;
    }
    bool changed = slide_left(row);
    for (int i = 0; i < 2; i++) {
        int temp = row[i];
        row[i] = row[3 - i];
        row[3 - i] = temp;
    }
    return changed;
}

bool move_left(t_grid *g)
{
    bool changed = false;
    for (int i = 0; i < 4; i++) {
        if (slide_left(g->grid[i])) {
            changed = true;
        }
    }
    return changed;
}

bool move_right(t_grid *g)
{
    bool changed = false;
    for (int i = 0; i < 4; i++) {
        if (slide_right(g->grid[i])) {
            changed = true;
        }
    }
    return changed;
}

bool move_up(t_grid *g)
{
    bool changed = false;
    for (int j = 0; j < 4; j++) {
        int col[4];
        for (int i = 0; i < 4; i++) {
            col[i] = g->grid[i][j];
        }
        if (slide_left(col)) {
            changed = true;
        }
        for (int i = 0; i < 4; i++) {
            g->grid[i][j] = col[i];
        }
    }
    return changed;
}

bool move_down(t_grid *g)
{
    bool changed = false;
    for (int j = 0; j < 4; j++) {
        int col[4];
        for (int i = 0; i < 4; i++) {
            col[i] = g->grid[i][j];
        }
        if (slide_right(col)) {
            changed = true;
        }
        for (int i = 0; i < 4; i++) {
            g->grid[i][j] = col[i];
        }
    }
    return changed;
}

bool is_game_over(t_grid *g)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (g->grid[i][j] == 0) {
                return false;
            }
            if (j < 3 && g->grid[i][j] == g->grid[i][j + 1]) {
                return false;
            }
            if (i < 3 && g->grid[i][j] == g->grid[i + 1][j]) {
                return false;
            }
        }
    }
    return true;
}

bool has_won(t_grid *g)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (g->grid[i][j] >= 2048) {
                return true;
            }
        }
    }
    return false;
}

void display_grid(t_grid *g)
{
    clear();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (g->grid[i][j] == 0) {
                mvprintw(i + 1, j * 5 + 1, "     ");
            } else {
                char buf[6];
                sprintf(buf, "%4d ", g->grid[i][j]);
                mvprintw(i + 1, j * 5 + 1, "%s", buf);
            }
        }
    }
    mvprintw(6, 1, "Use arrow keys to move, ESC to quit");
    refresh();
}

int main() {

    initscr();//no need for WINDOW *ptr 
    cbreak();// don't use raw() here so we don't have to handel signals
    noecho();// we can change this to echo() to make an extra bounus
    keypad(stdscr, TRUE);
    srand(time(NULL));
    
    t_grid game;
    memset(&game, 0, sizeof(t_grid));////////////////////////////////////////use ft_memset
    
    add_new_tile(&game);
    add_new_tile(&game);
    bool won = false;
    
    while (true) {
        display_grid(&game);
        if (has_won(&game) && !won) {
            won = true;
            mvprintw(7, 1, "You win! Keep playing or press ESC to quit");
        }
        if (is_game_over(&game)) {
            mvprintw(7, 1, "Game over! Press ESC to quit");
            refresh();
            while (getch() != 27);
            break;
        }
        
        int ch = getch();
        if (ch == 27) {
            break;
        }
        
        bool changed = false;
        switch (ch) {
            case KEY_LEFT:
                changed = move_left(&game);
                break;
            case KEY_RIGHT:
                changed = move_right(&game);
                break;
            case KEY_UP:
                changed = move_up(&game);
                break;
            case KEY_DOWN:
                changed = move_down(&game);
                break;
        }
        
        if (changed) {
            add_new_tile(&game);
        }
    }
    
    endwin();
    return 0;
}


