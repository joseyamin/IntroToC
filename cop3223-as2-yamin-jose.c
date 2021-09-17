/*
 *  UCF COP2332 Fall 2020 Assignment Solution
 *  Copyright 2020 Jose Yamin
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#ifdef _MSC_BUILD          // We're on a Microsoft compiler.
#define strcasecmp stricmp // We don't have strcasecmp, we have stricmp.
#endif

/* Remove carriage return and/or line feed characters from a string. */
void remove_crlf(char *s)
{
    char *t = s + strlen(s);

    t--;

    while ((t >= s) && (*t == '\n' || *t == '\r'))
    {
        *t = '\0'; // Clobber the character t is pointing at.
        t--;       // Decrement t.
    }
}

//returns the discriminant inputing the values
double discriminant(double a, double b, double c)
{
    return pow(b, 2) - (4 * a * c);
}
//returns positive answer of inputed values
double plus(double disc, double a, double b)
{
    return (-b + sqrt(disc)) / (2 * a);
}
//returns the negetive answer of inputed values
double minus(double disc, double a, double b)
{
    return (-b - sqrt(disc)) / (2 * a);
}
//prints out the plus or minus answers in the a+-bi form
double comp(double disc, double a, double b)
{
    double x = -b / (2 * a);
    double y = sqrt(-disc) / (2 * a);
    //checks to see if the a part of the equation is 0 to avoid it from printing out 0+-bi
    if (x == 0)
    {
        printf("x=+-%fi\n", y);
    }
    else
    {
        printf("x=%f+-%fi\n", x, y);
    }
    return 0;
}

int main(void)
{
    char a_buffer[128];
    char b_buffer[128];
    char c_buffer[128];

    double a;
    double b;
    double c;

    double x1;
    double x2;

    char do_again[128];

    while (1)
    {
        //asking and setting inputed values that are used in the equation
        printf("Enter the 'a' value.\n");
        fgets(a_buffer, 127, stdin);
        a = atof(a_buffer);
        printf("Enter the 'b' value.\n");
        fgets(b_buffer, 127, stdin);
        b = atof(b_buffer);
        printf("Enter the 'c' value.\n");
        fgets(c_buffer, 127, stdin);
        c = atof(c_buffer);

        //if statments for all the different possible cases of inputs

        //if all inputs are 0
        if (a == 0 && b == 0 && c == 0)
        {
            printf("You have inputed 0. Nice.\n");
        }
        //if a and b are 0 it will print the equation of y=
        else if (a == 0 && b == 0)
        {
            x1 = c;
            printf("The equation is y=%f\n", x1);
        }
        //when a is 0 so it will compute the x of the linear line and print it
        else if (a == 0)
        {
            x1 = -c / b;
            printf("Of the linear equation, x=%f\n", x1);
        }
        else
        {
            double disc = discriminant(a, b, c);
            //if discriminant is 0 then then there is one answer so only plus function is called and prined
            if (disc == 0)
            {
                x1 = plus(disc, a, b);
                printf("x=%f\n", x1);
            }
            //if discriminant is positive the 2 answers will be stored from plus and minus function and will be printed
            else if (disc > 0)
            {
                x1 = plus(disc, a, b);
                x2 = minus(disc, a, b);
                printf("x=%f and %f\n", x1, x2);
            }
            //else means the discriminant is negative which means a complex answer and will call the comp fucntion
            else
            {
                comp(disc, a, b);
            }
        }

        //ask user to play again if no it breaks and ends program
        printf("Press Enter if you want to input another set of values if not, enter 'no'.\n");
        fgets(do_again, 127, stdin);
        remove_crlf(do_again);
        if (strcasecmp(do_again, "no") == 0)
        {
            printf("Ok, bye!\n");
            break;
        }
    }
    return 0;
}