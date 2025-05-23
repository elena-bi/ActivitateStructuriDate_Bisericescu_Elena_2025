#include <stdio.h>
#include <string.h>

const char* happyBirthday(char name[]){
    if (strlen(name) > 1) {
        return "Happy birthday %s";
    }
    return "Happy birthday silly";
};

int main() {
    char isItMyBirthday[20];
    const char* message = "";
    char name[25];
    printf("\nWhat's your name?\n");
    scanf("%s", &name);
    printf("\nIs it your birthday?\n");
    char isItMyBirthday[1] = scanf("%c", &isItMyBirthday);

    if(isItMyBirthday == 'Y') {
        printf("%s", happyBirthday(name));
    }
    return 0;
}