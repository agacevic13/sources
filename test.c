#include <stdio.h>

//prototypes
extern int calculate_exp(char *str);

#define RED printf("\033[0;31m")
#define GREEN printf("\033[0;32m")
#define CLEAR printf("\033[0m")

void runAllTests(void)
{
    int result = calculate_exp("1+2");
    if(result == 3)
    {
        GREEN;
        printf("Test 1 Success\n");
        CLEAR;
    }
    else
    {
        RED;
        printf("Test 1 Fail! Expected: %d, Got: %d\n", 3, result);
        CLEAR;
    }

    result = calculate_exp("3-5");
    if(result == -2)
    {
        GREEN;
        printf("Test 2 Success\n");
        CLEAR;    }
    else
    {
        RED;
        printf("Test 2 Fail! Expected: %d, Got: %d\n", -2, result);
        CLEAR;
    }

    result = calculate_exp("4*9");
    if(result == 36)
    {
        GREEN;
        printf("Test 3 Success\n");
        CLEAR;    }
    else
    {
        RED;
        printf("Test 3 Fail! Expected: %d, Got: %d\n", 36, result);
        CLEAR;
    }

    result = calculate_exp("12/4");
    if(result == 3)
    {
        GREEN;
        printf("Test 4 Success\n");
        CLEAR;    }
    else
    {
        RED;
        printf("Test 4 Fail! Expected: %d, Got: %d\n", 3, result);
        CLEAR;
    }


     result = calculate_exp("(2-1)+9-10");
    if(result == 0)
    {
        GREEN;
        printf("Test 5 Success\n");
        CLEAR;    }
    else
    {
        RED;
        printf("Test 5 Fail! Expected: %d, Got: %d\n", 0, result);
        CLEAR;
    }

     result = calculate_exp("6+(8-2/2+3*2)");
    if(result == 19)
    {
        GREEN;
        printf("Test 6 Success\n");
        CLEAR;
    }
    else
    {
        RED;
        printf("Test 6 Fail! Expected: %d, Got: %d\n", 19, result);
        CLEAR;
    }

     result = calculate_exp("0*1-(0*2-0*3+((1+1)*0-1)+1)");
    if(result == 0)
    {
        GREEN;
        printf("Test 7 Success\n");
        CLEAR;
    }
    else
    {
        RED;
        printf("Test 7 Fail! Expected: %d, Got: %d\n", 0, result);
        CLEAR;
    }

     result = calculate_exp("((1*2)/2+2-(1-2))");
    if(result == 4)
    {
        GREEN;
        printf("Test 8 Success\n");
        CLEAR;
    }
    else
    {
        RED;
        printf("Test 8 Fail! Expected: %d, Got: %d\n", 4, result);
        CLEAR;
    }


     result = calculate_exp("0*3+5/5");
    if(result == 1)
    {
        GREEN;
        printf("Test 9 Success\n");
        CLEAR;
    }
    else
    {
        RED;
        printf("Test 9 Fail! Expected: %d, Got: %d\n", 1, result);
        CLEAR;
    }

     result = calculate_exp("2+2/2-(((0-1)+1)*0)");
    if(result == 3)
    {
        GREEN;
        printf("Test 10 Success\n");
        CLEAR;
    }
    else
    {
        RED;
        printf("Test 10 Fail! Expected: %d, Got: %d\n", 3, result);
        CLEAR;
    }
}

