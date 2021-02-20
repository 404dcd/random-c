#include <stdio.h>
#include <string.h>

void inputfill(int *sudoku) {
    int row = 0;
    while (row < 9) {
        char buf[10];
        printf("Row %d >>> ", row + 1);
        fgets(buf, sizeof buf, stdin);
        char *p;
        if(p=strchr(buf, '\n')){ // check exist newline
            *p = 0;
        } else {
            char c;
            while ((c = getchar()) != EOF && c != '\n'); // clear upto newline
        }

        for (int i = 0; i < 9; i++) {
            if ('0' > buf[i] || buf[i] > '9') {
                row--;
                printf("Bad input, enter 9x 0-9\n");
                break;
            }
            sudoku[(row*9) + i] = buf[i] - 48;
        }
        row++;
    }
    printf("\n");
}


void display(int *sudoku) {
    for (int i = 0; i < 81; i++) {
        printf("%d ", sudoku[i]);
        if (i % 3 == 2) {
            printf(" ");
        }
        if (i % 9 == 8) {
            printf("\n");
            if (i % 27 == 26) {
                printf("\n");
            }
        }
    }
}

int possible(int *sudoku, int pos) {
    int bad = 0;
    int c;
    int startrow = (pos / 9) * 9;
    for (c = startrow; c < startrow+9; c++) {
        bad |= 1 << sudoku[c];
    }

    int startcol = pos % 9;
    for (c = startcol; c < startcol+81; c+=9) {
        bad |= 1 << sudoku[c];
    }

    int sboxc = (startcol / 3) * 3;
    int sboxr = (startrow / 27) * 27;
    for (int offset = 0; offset < 27; offset += 9) {
        int grp = sboxc + sboxr + offset;
        for (c = grp; c < grp+3; c++) {
            bad |= 1 << sudoku[c];
        }
    }
    return ~bad;
}

int main() {
    int sudoku[81];

    inputfill(sudoku);

    display(sudoku);

    return 0;
}