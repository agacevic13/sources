#include <stdio.h>
//#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#include "functions.h"
//samo + i -
// da pitam za expression string
// idi kroz string i prepoznavaj cifru ili - i +
//validni karakteri 0-9, i +, -
// bool funkcija sto vraca true ili false ako je expression valid
//da li je karakter valid
// prepoznati delimetere
// dva niza - brojevi i delimiteri
// izracunati

extern void runAllTests(void);

int main(void)
{
    char *str = calloc(100, sizeof(char));
    char valid_char[]= "0123456789+-*/()";
    char choice;
    runAllTests();

    while(true)
    {
        printf("Input an expression using +, -, *, / operators (no white spaces):\n");
        fgets(str, 100, stdin);

        size_t length = strlen(str);

        if (length > 0 && str[length - 1] == '\n')
        {
            str[length - 1] = '\0'; // Replace newline with null character
        }


        if (exp_valid(str, valid_char))
        {
            int result = calculate_exp(str);
            printf("Valid, %i\n", result);
            break;
        }
        else
        {
            printf("Invalid\n");
        }
    }

    while(true)
    {
        printf("Do you want to expand the last input or enter a new one? (e for expand, n for new, q to quit):\n");
        scanf(" %c", &choice);

        if(choice == 'e')
        {
            printf("%s", str);
            char temp[100];

            scanf("%s", temp);
            // combine both inputs
            strncat(str, temp, sizeof(str) - strlen(str) - 1);
            int i = strlen(str);

            if (exp_valid(str, valid_char))
            {
                int result = calculate_exp(str);
                printf("Valid, %i\n", result);
            }
            else
            {
                printf("Invalid\n");
            }

        }

        else if(choice == 'n')
        {
            printf("Enter a new input:\n");
            scanf("%s", str);
            //i++;

            if (exp_valid(str, valid_char))
            {
                int result = calculate_exp(str);
                printf("Valid, %i\n", result);
            }
            else
            {
                printf("Invalid\n");
            }
        }
        else if(choice == 'q')
        {
            break;
        }

        else
        {
            printf("Invalid input, try again.\n");
        }

    }
    free(str);
    str=NULL;
}

