// Header file for input output functions
#include <stdio.h>
#include <stdbool.h>

// Main function: entry point for execution
int main() {
    //initialize
    int x;
    //declare
    x = 23;

    int y = 23;
    float avg = 23.1;
    char grade = 'A'; // stores a single character
    char name[] = "Elena"; //stores an array a characters, similar to a string
    bool isTrue = false;

    //The use of format specifiers
    //the % is a format specifier and placeholder, the letter after indicates the data type

    printf("Hello World %d, %d\n", x, y);
    printf("The first letter in my name is %c\n", name[0]);
    printf("My name is %s\n", name);
    printf("I have good grades %s\n", isTrue ? "true" : "false");

    //For floats or similar:

    //%.2 -> this will only display 2 decimals
    //%3 -> this adds minimum space width between the last character and the value after (more a caveat)
    //%- -> this will allign the data to the right but if you have also mentioned the width that will still be added but at the 
    //      end of the line
    float item1Price = 12.657;
    printf("Item 1 price is: %9.2f", item1Price);

    //How to define a constant:
    const int roomLength = 10; //value is not changing after its declaration
    return 0;
}