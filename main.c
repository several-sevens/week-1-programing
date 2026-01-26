#include <stdio.h>

int main(void) {
    float ms;

    printf("please enter m/s to convert to mph: ");
    scanf("%f", &ms);

    // I combined the declaration and the math here
    float mph = ms * 2.23694;

    printf("this is: %f mph\n", mph);

    return 0; // Added the missing semicolon here
}