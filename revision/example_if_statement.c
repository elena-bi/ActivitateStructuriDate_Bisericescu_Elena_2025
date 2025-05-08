#include <stdio.h>

int main() {
    int num;
    printf("\nChoose a number\n");
    scanf("%d", &num);
    if (num % 2 == 0) {
        printf("\nYour number is even");
    } else {
        printf("\nYour number is odd");
    }
    return 0;
}