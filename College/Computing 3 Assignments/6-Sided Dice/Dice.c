#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main() {
    int dice = 0;
    int sum = 0;
    bool b = true;

    while (b == true) {
        printf("Enter the amount of dice you want to roll(in numbers and must be 2-5): ");
        scanf("%d", &dice);
        if (dice > 5 || dice < 2) {
            printf("ERROR::DICE::AMOUNT is invalid\n");
            continue;
        }

        int array[dice];
        for (int i = 0; i < dice; i++) {
            array[i] = (rand() % (6)) + 1;
            sum += array[i];
        }

        for (int i = 0; i < dice; i++) {
            printf("Value for die %d", i + 1);
            printf(" is %d \n", array[i]);
        }

        printf("The sum is  %d \n", sum);
        printf("The average is %d \n", sum / dice);

        dice = 0;
        sum = 0;
    }
}