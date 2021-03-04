#include <stdio.h>

void clean_stdin(void) {
    int c;
    do {
        c = getc(stdin);
    } while (c != '\n' && c != EOF);
}

void get_seeds(int *board, int player, int* seeds, int* cell) {
    int ui;
    while (1) {
        printf("Player %d, select a column >>> ", player ? 2 : 1);
        ui = getc(stdin);
        clean_stdin();
        ui -= '0';
        if (ui >= 1 && ui <= 6) {
            ui--;
            *seeds = board[player + ui];
            if (seeds) {
                board[player + ui] = 0;
                *cell = player + ui;
                return;
            }
        }
        printf("Error: enter 1<=x<=6, for a cell containing seeds.");
    }
}

int detect(int *board) {
    for (int player = 0; player < 14; player += 7) {
        for (int i = 0; i < 6; i++) {
            if (board[player + i]) {
                return 0;
            }
        }
        return player;
    }
}

void display(int *board, int player) {
    int other = player ? 0 : 7;
    printf("   ");
    for (int i = other + 5; i >= other; i--) {
        printf("%02d ", board[i]);
    }
    printf("\n%02d\t\t     %02d\n   ", board[other ? 13 : 6], board[player ? 13 : 6]);
    for (int i = player; i <= player + 5; i++) {
        printf("%02d ", board[i]);
    }
    printf("\n");
}

void do_move(int *board, int player) {
    int seeds;
    int cell;
    int mystore = player ? 13 : 6;
    int otherstore = player ? 6 : 13;
    while (1) {
        display(board, player);
        if (detect(board)) {
            return;
        }
        get_seeds(board, player, &seeds, &cell);
        
        while (seeds) {
            cell = (cell + 1) % 14;
            if (cell != otherstore) {
                board[cell]++;
                seeds--;
            }
        }

        if (cell != mystore) {
            if (board[cell] == 1 && !board[12 - cell]) {
                printf("You captured seeds.\n");
                board[cell] = 0;
                board[mystore] += board[12 - cell] + 1;
                board[12 - cell] = 0;
            }
            display(board, player);
            printf("Turn over, flipping board.\n\n");
            break;
        }
    }
}

int main() {
    int board[14];
    int player = 0;
    int result = 0;

    for (int i = 0; i < 14; i++) {
        board[i] = (i % 7) - 6 ? 4 : 0;
    }

    while (!result) {
        do_move(board, player);

        player = player ? 0 : 7;
        result = detect(board);
    }

    player = result ? 0 : 7;
    for (int i = 0; i < 6; i++) {
        board[player ? 6 : 13] += board[player + i];
    }

    printf("Player 1 scored: %d\n", board[6]);
    printf("Player 2 scored: %d\n", board[13]);
    return 0;
}