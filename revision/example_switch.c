#include <stdio.h>

int main() {
    char grade;
    printf("\nChoose a number\n");
    scanf("%c", &grade);
    
    switch(grade) {
        case 'A':
            printf("Congrats");
        case 'B':
            printf("Nice");
    }
    return 0;
}