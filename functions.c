#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

static bool char_valid(char c, char valid_char[])
{
    int size = strlen(valid_char);
    for (int i = 0; i < size; i++)
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
    size_t lenght = strlen(str);
    for (size_t i = 0; i < lenght; i++)
    {
        if (isspace((int)str[i]))
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
    char valid_operator[] = "+-*/()";
    int lenght = strlen(valid_operator);
    for (int i = 0; i < lenght; i++)
    {
        if (c == valid_operator[i])
        {
            return 1;
        }
    }
    return 0;
}

static int find_matching_parenthesis(char *str, int close_index)
{
    int count = 1;
    for (int i = close_index - 1; i >= 0; i--)
    {
        if (str[i] == ')')
            count++;
        else if (str[i] == '(')
            count--;
        if (count == 0)
            return i;
    }
    return -1;
}

int calculate_exp(char *str)
{
    int lenght = strlen(str);
    int i = 0;
    int j = 0;
    int nizOperanada[10];
    char nizOperatora[10];
    int number = 0;
    int operator_counter = 0;
    int operanda_counter = 0;

    // Obrada zagrada: prvo tražimo zatvorene zagrade
    for (i = 0; i < lenght; i++)
    {
        if (str[i] == ')')
        {
            int close_index = i;
            int open_index = find_matching_parenthesis(str, close_index);
            if (open_index == -1)
            {
                printf("Mismatched parentheses\n");
                return -1;
            }

            char *between = calloc(50, sizeof(char));
            strncpy(between, str + open_index + 1, close_index - open_index - 1);
            between[close_index - open_index - 1] = '\0';

            int sub_result = calculate_exp(between);
            free(between);

            // Zamena izraza unutar zagrada rezultatom
            char *new_str = calloc(50, sizeof(char));
            strncpy(new_str, str, open_index);
            char sub_result_str[20];
            sprintf(sub_result_str, "%d", sub_result);
            strcat(new_str, sub_result_str);
            strcat(new_str, str + close_index + 1);

            int final_result = calculate_exp(new_str);
            free(new_str);

            return final_result;
        }
    }

    // Parsiranje operanda i operatora kada nema više zagrada
    for (i = 0; i < lenght; i++)
    {
        // Obrada brojeva, uključujući negativne brojeve
        if (isdigit((int)str[i]) || (str[i] == '-' && (i == 0 || is_operator(str[i - 1]))))
        {
            bool is_negative = false;
            if (str[i] == '-')
            {
                is_negative = true;
                i++;
            }

            number = 0;  // Reset broj za svaki broj
            while (i < lenght && isdigit((int)str[i]))
            {
                number = number * 10 + (str[i] - '0');
                i++;
            }
            i--;  // Vrati indeks jer će petlja povećati

            if (is_negative)
            {
                number = -number;
            }

            nizOperanada[operanda_counter] = number;
            operanda_counter++;
        }
        // Obrada operatora
        else if (is_operator(str[i]))
        {
            nizOperatora[operator_counter] = str[i];
            operator_counter++;
        }
        else
        {
            printf("Invalid character found...\n");
            return 1;
        }
    }

    // Obrada operatora sa višim prioritetom (* i /)
    for (i = 0; i < operator_counter; i++)
    {
        if (nizOperatora[i] == '*' || nizOperatora[i] == '/')
        {
            if (nizOperatora[i] == '*')
            {
                nizOperanada[i] = nizOperanada[i] * nizOperanada[i + 1];
            }
            else if (nizOperatora[i] == '/')
            {
                nizOperanada[i] = nizOperanada[i] / nizOperanada[i + 1];
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

    // Obrada operatora sa nižim prioritetom (+ i -)
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
