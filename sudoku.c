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



int main() {
    int sudoku[81];

    inputfill(sudoku);

    display(sudoku);

    return 0;
}