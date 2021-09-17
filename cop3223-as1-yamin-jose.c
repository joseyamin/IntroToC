/*
 *  UCF COP2332 Fall 2020 Assignment Solution
 *  Copyright 2020 Jose Yamin
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
    if(x==0){
        printf("x=+-%fi\n",y);
    }else{
        printf("x=%f+-%fi\n", x, y);
    }
    return 0;
}

int main(void)
{
    double x1;
    double x2;
    //values that are used in the equation
    double a = -5;
    double b = -3;
    double c = -3;

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

    return 0;
}