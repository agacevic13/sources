#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "functions.h"

static bool char_valid(char c, char valid_char[])
{
    int size = strlen(valid_char);
    int i = 0;

    for (i = 0; i < size; i++)
    {
        if (c == valid_char[i])
        {
            return true;
        }
    }

    return false;
}



bool exp_valid(char *str, char valid_char[])
{
    int lenght = strlen(str);
    int i;
    for (i = 0; i < lenght; i++)
    {
        if (isspace(str[i]))
        {
            return false;
        }
        if (!char_valid(str[i], valid_char))
        {
        return false;
        }
    }
    return true;
}


static char is_operator(char c)
{
    char valid_operator[]= "+-*/()";
    int lenght = strlen(valid_operator);
    int i = 0;
    for (i = 0; i < lenght; i++)
    {
        if (c == valid_operator[i])
        {
            return 1;
        }
    }
    return 0;
}


static int find_matching_parenthesis(char *str, int open_index)
{
    int count = 1;
    int i;
    for (i = open_index + 1; i < strlen(str); i++)
    {
        if (str[i] == '(')
            count++;
        else if (str[i] == ')')
            count--;
        if (count == 0)
            return i;
    }
    return -1;
}

int calculate_exp(char *str)
{
    int i = 0;
    int j = 0;
    int nizOperanada[10];
    char nizOperatora[10];
    int number = 0;
    int lenght = strlen(str);
    int operator_counter = 0;
    int operanda_counter = 0;

//determing parenthesis
     while (i < lenght)
     {
        if (str[i] == '(')
        {
            int open_index = i;
            int close_index = find_matching_parenthesis(str, open_index);
            if (close_index == -1)
            {
                printf("Mismatched parentheses\n");
                return -1;
            }

            char *between = calloc(50, sizeof(char));
            strncpy(between, str + open_index + 1, close_index - open_index - 1);

            int sub_result = calculate_exp(between);

            free(between);

            char *result_str = calloc(20, sizeof(char));
            sprintf(result_str, "%d", sub_result);

            char *new_str = calloc(50, sizeof(char));
            strncpy(new_str, str, open_index);
            strcat(new_str, result_str);
            strcat(new_str, str + close_index + 1);

            free(result_str);

            int final_result = calculate_exp(new_str);

            free(new_str);

            return final_result;

            //free(between);
            //free(result_str);
        }
        i++;

    }
//determining operande i operatore
    for (i = 0; i < lenght; i++)
    {
        //check and get numbers
        if (isdigit(str[i]))
        {
            number = number * 10 + (str[i] - '0');
            if (i == lenght - 1 || !isdigit(str[i+1]))
            {
                nizOperanada[operanda_counter] = number;
                operanda_counter++;

            }
        }
        //what to do if char is operator
        else if (is_operator(str[i]))
        {
            char operator = str[i];
            //nizOperanada[operanda_counter] = number;
            nizOperatora[operator_counter] = operator;
            operator_counter++;
            number = 0;
        }
        else
        {
            printf("Shouldn't be here...\n");
            return 1;
        }
    }
    for (i = 0; i < operator_counter; i++)
    {
        if (nizOperatora[i] == '*' || nizOperatora[i] == '/')
        {
            if (nizOperatora[i] == '*')
            {
                nizOperanada[i] = nizOperanada[i] * nizOperanada[i+1];
            }
            else if (nizOperatora[i] == '/')
            {
                nizOperanada[i] = nizOperanada[i] / nizOperanada[i+1];

            }

            for (j = i + 1; j < operator_counter; j++)
            {
                nizOperanada[j] = nizOperanada[j + 1];
                nizOperatora[j - 1] = nizOperatora[j];
            }

            operator_counter--;
            i--;
        }
    }

    int result = nizOperanada[0];
    for (i = 0; i < operator_counter; i++)
    {
        if (nizOperatora[i] == '-')
            {
                result -= nizOperanada[i + 1];
            }
        else if (nizOperatora[i] == '+')
            {
                result += nizOperanada[i + 1];
            }
    }

    return result;
}
