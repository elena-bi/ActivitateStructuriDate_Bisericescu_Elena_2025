#include <stdio.h>

const char* happyBirthday(){
    return "Happy birthday silly";
};

int main() {
    char isItMyBirthday = 'a';
    const char* message = "";
    printf("\nIs it your birthday?\n");
    scanf("%c", &isItMyBirthday);
    
    if(isItMyBirthday == 'Y') {
        message = happyBirthday();
        printf("%s", message);
    }
    return 0;
}