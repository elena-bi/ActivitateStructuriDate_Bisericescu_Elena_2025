#include <stdio.h>
#include <string.h>

int main()
{
    int age;
    char name[25];

    // printf("How old are you?\n");
    // scanf("%d", &age);
    // printf("\nThe age is %d", age);


    // Use another way to get input from console
    printf("\nWhat's your name\n");
    fgets(name, 25, stdin);
    name[strlen(name) - 1] = '\0';
    printf("\nMy name is %s", name);
    return 0;
    
}