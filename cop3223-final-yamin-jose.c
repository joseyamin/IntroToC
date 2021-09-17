/*
 *  UCF COP2332 Fall 2020 Assignment Solution
 *  Copyright 2020 Jose Yamin
 */

//calculator project, will recevie ur inputed number and or special case such as c b ca. Pogram can be ended at any time by entering q to quit. After a number is entered an operation can be called and some operations need a second number inputed. With the result u can sto to store or keep working on the result until clear, c to reset.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

//function to add the a number to history in the next place
void *add_history(double *nums, double num, int *history_size)
{
  *history_size = *history_size + 1;
  nums[*history_size-1]=num;
}

// when user types rcl this will ask which place to recall and return the stored variable return nan and error if 0-9 is not inputed USE ONLY WHEN ASKING FOR NUM
double recall_storage_input(double *storage, FILE *ofp)
{
  char buf[32];
  int place = 0;
  printf("Which value do you want to recall from storage, 0-9.\n");
  fgets(buf, 31, stdin);
  remove_crlf(buf);
  place = atof(buf);
  if (place > 9 || place < 0)
  {
    printf("error value is not 0-9.\n");
    return NAN;
  }
  printf("Recalled: %f\n", storage[place]);
  fprintf(ofp, "Recalled: %f\n", storage[place]);
  return storage[place];
}
//when user types rcl this will use the last number as the place location to recall and return the stored variable return nan and error if number is not 0-9 USE ONLY WHEN ASKING FOR NUM
double recall_storage_operation(double num, double *storage, FILE *ofp)
{
  int place = num;
  if (place > 9 || place < 0)
  {
    printf("error value is not 0-9.\n");
    fprintf(ofp, "error\n");
    return NAN;
  }
  printf("From loactation %d, Recalled: %f\n", place, storage[place]);
  fprintf(ofp, "From loactation %d, Recalled: %f\n", place, storage[place]);
  return storage[place];
}
//the last result/number on screen will be stored into the users storage array by asking which place 0-9, if not it will print error.
void store_storage(double num, double *storage, FILE *ofp)
{
  char buf[32];
  int place = 0;
  printf("Where do you want to store %f, 0-9.\n", num);
  fgets(buf, 31, stdin);
  remove_crlf(buf);
  place = atof(buf);
  if (place > 9 || place < 0)
  {
    fprintf(ofp, "not a valid location\n");
    printf("error value is not 0-9.\n");
  }
  else
  {
    storage[place] = num;
    fprintf(ofp, "Stored: %f in %d.\n", storage[place], place);
    printf("Stored: %f in %d.\n", storage[place], place);
  }
}
//funtion to clear users storage and set all to 0
void clear_storage(double *storage)
{
  for (int i = 0; i < 10; i++)
  {
    storage[i] = 0;
  }
  printf("storage cleared\n");
}

//will go show the last result and ask to enter or b to go back again, this can be done until the user presses enter on the result they want to return it or when last result is reached it will return it
double back(double *nums, int *history_size, FILE *ofp)
{
  int count = *history_size - 1;
  char buf[32];
  printf("%lf is your number, enter 'b' to go back again or enter to countinue.\n", nums[count]);
  fgets(buf, 31, stdin);
  remove_crlf(buf);
  while (strcmp(buf, "b") == 0)
  {
    count--;
    if (count == -1)
    {
      count = 0;
      printf("This is as far as you got, %lf is your number.\n", nums[count]);
      fprintf(ofp, "%f\n", nums[count]);
      return nums[count];
    }
    else
    {
      printf("%lf is your number, b to go back again or enter to countinue.\n", nums[count]);
      fgets(buf, 31, stdin);
      remove_crlf(buf);
    }
  }
  fprintf(ofp, "%f\n", nums[count]);
  add_history(nums, nums[count], history_size);
  return nums[count];
}
//ask user and returns the number they want such as pi, e, or a number, if it is special cases such as c, ca, b,rcl, q and will call those functions accordingly and return nan so we know no number was returned
double get_num(double *nums, double *result, int *history_size, double *storage, FILE *ofp)
{
  char buf[32];
  while (strcmp(buf, "q") != 0)
  {
    printf("Enter a number.\n");
    fgets(buf, 31, stdin);
    remove_crlf(buf);
    if (strcmp(buf, "pi") == 0)
    {
      fprintf(ofp, "pi\n");
      add_history(nums, M_PI, history_size);
      return M_PI;
    }
    else if (strcmp(buf, "e") == 0)
    {
      fprintf(ofp, "e\n");
      add_history(nums, M_E, history_size);
      return M_E;
    }
    else if (strcmp(buf, "c") == 0)
    {
      add_history(nums, 0, history_size);
      fprintf(ofp, "c\n");
      printf("0\n");
      return NAN;
    }
    else if (strcmp(buf, "ca") == 0)
    {
      fprintf(ofp, "ca\n");
      clear_storage(storage);
      return NAN;
    }
    else if (strcmp(buf, "q") == 0)
    {
      fprintf(ofp, "q\n");
      free(nums);
      free(history_size);
      free(storage);
      free(result);
      fclose(ofp);
      printf("Program has been quit\n");
      exit(0);
    }
    else if (strcmp(buf, "b") == 0)
    {
      fprintf(ofp, "b\n");
      return back(nums, history_size, ofp);
    }
    else if (strcmp(buf, "rcl") == 0)
    {
      fprintf(ofp, "rcl\n");
      return recall_storage_input(storage, ofp);
    }
    else
    {
      fprintf(ofp, "%lf\n", atof(buf));
      add_history(nums, atof(buf), history_size);
      return atof(buf);
    }
  }
}
//will use the last numbered to ask what to operation to do with it. if binary operation it will call get num for the second num. if an error occurs or a special case is called such as c ca it will not proceed and return to step one. else it will go on ina loop for ever until a number is nan. can also store values or recall and even quit
void do_operation(double num, double *result, double *nums, int *history_size, double *storage, FILE *ofp)
{
  *result = num;
  char buf[32];
  int proceed = 1;
  double num2;

  while (proceed == 1)
  {
    printf("Enter Operation you want to do to %lf.\n", num);
    fgets(buf, 31, stdin);
    remove_crlf(buf);
    if (strcmp(buf, "+") == 0)
    {
      fprintf(ofp, "+\n");
      num2 = get_num(nums, result, history_size, storage, ofp);
      if (num2 != num2)
      {
        *result = NAN;
        proceed = 0;
      }
      else
      {
        *result = num + num2;
      }
    }
    else if (strcmp(buf, "-") == 0)
    {
      fprintf(ofp, "-\n");
      num2 = get_num(nums, result, history_size, storage, ofp);
      if (num2 != num2)
      {
        *result = NAN;
        proceed = 0;
      }
      else
      {
        *result = num - num2;
      }
    }
    else if (strcmp(buf, "x") == 0)
    {
      fprintf(ofp, "x\n");
      num2 = get_num(nums, result, history_size, storage, ofp);
      if (num2 != num2)
      {
        *result = NAN;
        proceed = 0;
      }
      else
      {
        *result = num * num2;
      }
    }
    else if (strcmp(buf, "/") == 0)
    {
      fprintf(ofp, "/\n");
      num2 = get_num(nums, result, history_size, storage, ofp);
      if (num2 == 0 || num2 != num2)
      {
        if (num2 == 0)
        {
          fprintf(ofp, "error\n");
          printf("error\n");
        }
        proceed = 0;
        *result = NAN;
      }
      else
      {
        *result = num / num2;
      }
    }
    else if (strcmp(buf, "^") == 0)
    {
      fprintf(ofp, "^\n");
      num2 = get_num(nums, result, history_size, storage, ofp);
      if (num2 != num2)
      {
        *result = NAN;
        proceed = 0;
      }
      else
      {
        *result = pow(num, num2);
      }
    }
    else if (strcmp(buf, "sin") == 0)
    {
      fprintf(ofp, "sin\n");
      if (num != num)
      {
        *result = NAN;
        proceed = 0;
      }
      else
      {
        *result = sin(num);
      }
    }
    else if (strcmp(buf, "cos") == 0)
    {
      fprintf(ofp, "cos\n");
      if (num != num)
      {
        *result = NAN;
        proceed = 0;
      }
      else
      {
        *result = cos(num);
      }
    }
    else if (strcmp(buf, "tan") == 0)
    {
      fprintf(ofp, "tan\n");
      if (num != num)
      {
        *result = NAN;
        proceed = 0;
      }
      else
      {
        *result = tan(num);
        if (*result != *result)
        {
          fprintf(ofp, "error\n");
          printf("error\n");
        }
      }
    }
    else if (strcmp(buf, "arcsin") == 0)
    {
      fprintf(ofp, "arcsin\n");
      if (num != num || num > 1 || num < -1)
      {
        if (num > 1 || num < -1)
        {
          fprintf(ofp, "error\n");
          printf("error\n");
        }
        *result = NAN;
        proceed = 0;
      }
      else
      {
        *result = asin(num);
      }
    }
    else if (strcmp(buf, "arccos") == 0)
    {
      fprintf(ofp, "arccos\n");
      if (num != num || num > 1 || num < -1)
      {
        if (num > 1 || num < -1)
        {
          fprintf(ofp, "error\n");
          printf("error\n");
        }
        *result = NAN;
        proceed = 0;
      }
      else
      {
        *result = acos(num);
      }
    }
    else if (strcmp(buf, "arctan") == 0)
    {
      fprintf(ofp, "arctan\n");
      if (num != num)
      {
        *result = NAN;
        proceed = 0;
      }
      else
      {
        *result = atan(num);
      }
    }
    else if (strcmp(buf, "root") == 0)
    {
      fprintf(ofp, "root\n");
      if (num < 0 || num != num)
      {
        if (num < 0)
        {
          fprintf(ofp, "error\n");
          printf("error\n");
        }
        *result = NAN;
        proceed = 0;
      }
      else
      {
        *result = sqrt(num);
      }
    }
    else if (strcmp(buf, "abs") == 0)
    {
      fprintf(ofp, "abs\n");
      if (num != num)
      {
        *result = NAN;
        proceed = 0;
      }
      else
      {
        *result = fabs(num);
      }
    }
    else if (strcmp(buf, "inv") == 0)
    {
      fprintf(ofp, "inv\n");
      if (num == 0 || num != num)
      {
        if (num == 0)
        {
          fprintf(ofp, "error\n");
          printf("error\n");
        }
        *result = NAN;
        proceed = 0;
      }
      else
      {
        *result = 1 / num;
      }
    }
    else if (strcmp(buf, "log") == 0)
    {
      fprintf(ofp, "log\n");
      if (num <= 0 || num != num)
      {
        if (num <= 0)
        {
          fprintf(ofp, "error\n");
          printf("error\n");
        }
        *result = NAN;
        proceed = 0;
      }
      else
      {
        *result = log10(num);
      }
    }
    else if (strcmp(buf, "log2") == 0)
    {
      fprintf(ofp, "log2\n");
      if (num <= 0 || num != num)
      {
        if (num <= 0)
        {
          fprintf(ofp, "error\n");
          printf("error\n");
        }
        *result = NAN;
        proceed = 0;
      }
      else
      {
        *result = log2(num);
      }
    }
    else if (strcmp(buf, "sto") == 0)
    {
      fprintf(ofp, "sto\n");
      store_storage(num, storage, ofp);
    }
    else if (strcmp(buf, "rcl") == 0)
    {
      fprintf(ofp, "rcl\n");
      *result = recall_storage_operation(num, storage, ofp);
    }
    else if (strcmp(buf, "c") == 0)
    {
      fprintf(ofp, "c\n");
      proceed = 0;
      *result = NAN;
      add_history(nums, 0, history_size);
      printf("0\n");
    }
    else if (strcmp(buf, "ca") == 0)
    {
      fprintf(ofp, "ca\n");
      clear_storage(storage);
      proceed = 0;
      *result = NAN;
    }
    else if (strcmp(buf, "q") == 0)
    {
      fprintf(ofp, "q\n");
      printf("Program has been quit\n");
      free(storage);
      free(nums);
      free(result);
      free(history_size);
      fclose(ofp);
      exit(0);
    }
    else
    {
      fprintf(ofp, "error\n");
      printf("error\n");
      *result = NAN;
    }

    if (*result == *result)
    {
      printf("Result: %lf\n", *result);
      fprintf(ofp, "%17.17lf\n", *result);
      add_history(nums, *result, history_size);
      num = *result;
    }
    else
    {
      proceed = 0;
    }
  }
}
//main where eevrything is done
int main(void)
{
  //all pointers needed to store crucial information such as nums for the history the the result for current result/num working on, history size to know the size of history, storage to store the users variables and file of ofp.
  char operation[32];
  char buf[32];
  double num;
  double *result;
  double *nums;
  int *history_size;
  double *storage;
  FILE *ofp = fopen("calculator-output.txt", "w");
  storage = malloc(sizeof(double) * 10);
  history_size = malloc(sizeof(int));
  *history_size=0;
  result = malloc(sizeof(double));
  nums = malloc(sizeof(double)*1000);
  //this will go on forever only way to end it is by using q to quit the program when prompted to enter anything, the user will input a number if the number is not a number/special case then it will restart, if it is a number then it will do operation with that number.
  while (1 == 1)
  {
    printf("Step one.\n");
    num = get_num(nums, result, history_size, storage, ofp);
    if (num == num)
    {
      do_operation(num, result, nums, history_size, storage, ofp);
    }
  }
  //will never get here
  return 0;
}