#include <stdio.h>

void clean_stdin(void) {
    int c;
    do {
        c = getc(stdin);
    } while (c != '\n' && c != EOF);
}

void display(int *board) {
    for (int i = 0; i < 9; i++) {
        if (!(i % 3)) {
            printf("\n");
        }

        switch (board[i]) {
            case 1:
                printf("X ");
                break;
            case 2:
                printf("O ");
                break;
            default:
                printf(". ");
        }
    }
    printf("\n");
}

int detect(int *board) { // -1 Draw, 0 in play, 1 X win, 2 O win
    for (int offset = 0; offset < 9; offset += 3) { // Row win detect
        int win = board[offset];
        if (win) {
            if (win == board[offset+1] && win == board[offset+2]) {
                return win;
            }
        }
    }

    for (int offset = 0; offset < 3; offset++) { // Col win detect
        int win = board[offset];
        if (win) {
            if (win == board[offset+3] && win == board[offset+6]) {
                return win;
            }
        }
    }

    int win = board[4];
    if (win) { // Diagonal win detect
        if (win == board[0] && win == board[8]) {
            return win;
        }
        if (win == board[2] && win == board[6]) {
            return win;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (!board[i]) {
            return 0;
        }
    }

    return -1;
}

void AIplay(int *board, int player) { // Under construction
    for (int i = 0; i < 9; i++) {
        if (!board[i]) {
            board[i] = player
            int res = detect(board);
            board[i] = 0
            if res == player {
                return i
            }
        }
    } 
}

void humanplay(int *board, int player) {
    while (1) {
        printf("Use keypad to indicate location >>> ");
        int ui = getc(stdin);
        clean_stdin();
        ui -= '0';
        if (ui >= 1 && ui <= 9) {
            ui--;
            int location = 2 - (ui / 3);
            location *= 3;
            location += ui % 3;
            if (!board[location]) {
                board[location] = player;
                return;
            }
        }
        printf("Bad input: enter 1<=x<=9, 7 = top left, 3 = bottom right, blank space.\n");
    }
}


int main() {
    int board[9];
    int player = 1;
    int result = 0;
    int computer = 2;

    for (int i = 0; i < 9; i++) {
        board[i] = 0;
    }

    printf("Computer goes first? y/n >>> ");
    int ui = getc(stdin);
    clean_stdin();
    if (ui == 'y' || ui == 'Y') {
        computer = 1;
    }

    display(board);
    while (!result) {

        if (player == computer) {
            AIplay(board, player);
        } else {
            humanplay(board, player);
        }

        display(board);

        result = detect(board);

        player &= 1;
        player++;
    }

    switch (result) {
        case 1:
            printf("Winner: X\n");
            break;
        case 2:
            printf("Winner: O\n");
            break;
        case -1:
            printf("Draw.\n");
    }

    return 0;
}