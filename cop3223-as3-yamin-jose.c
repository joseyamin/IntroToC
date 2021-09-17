/*
 *  UCF COP2332 Fall 2020 Assignment Solution
 *  Copyright 2020 Jose Yamin
 */

//this program gets data from input file sucha as the title and cords and outputs to the out put file. Then computes slope and intercept and outputs that as well. Then creates arrays for x and y values for the certain cases and inputed values. At the end it prints all results.
#include <stdio.h>
#include <string.h>

//retuns slope from 2 given points
double find_slope(double x1,double y1, double x2,double y2){
  return (y1-y2)/(x1-x2);
}

//returns intercept with the slope and point
double find_intercept(double x,double y,double slope){
  return (slope*-x)+y;
}

//puts all y points within the y array by computing x array values correspondingly
void create_y_array(double *x_array,double *y_array,int size,double slope,double intercept){
  for(int i=0;i<size;i++){
    y_array[i]=(slope*x_array[i])+intercept;
  }
}

//outputs cords from the arrays into file with lined decimals
void print_cords(double *x_array,double *y_array, int size,FILE *ofp)
{
    for (int i = 0; i < size; i++)
    {
      fprintf(ofp,"(%15lf,%15lf)\n",x_array[i],y_array[i]);
    }
    fprintf(ofp,"\n");
}

int main(void) 
{
  //creat and open files
  FILE *ifp;
  FILE *ofp;
  ifp=fopen("cop3223-as3input.txt","r");
  ofp=fopen("cop3223-as3output-yamin-jose.txt","w");

  //gets inputed title and outputs it
  char title[128];
  fgets(title,127,ifp);
  fprintf(ofp,"Title: %s\n",title);

  //scan and store cords from input file
  fprintf(ofp,"The 2 cords:\n");
  double x1,y1,x2,y2;
  fscanf(ifp,"%lf, %lf\n",&x1,&y1);
  fprintf(ofp,"(%lf, %lf)\n",x1,y1);
  fscanf(ifp,"%lf, %lf\n",&x2,&y2);
  fprintf(ofp,"(%lf,%lf)\n\n",x2,y2);

  //find, create, and print slope and intercept 
  double slope=find_slope(x1,y1,x2,y2);
  double intercept=find_intercept(x1,y1,slope);
  fprintf(ofp,"Slope: %f and Intercept: %f\n\n",slope,intercept);

  //create each array with the x's
  double array_set1_x[11]={0,1,2,3,4,5,6,7,8,9,10};
  double array_set2_x[11]={0,-1,-2,-3,-4,-5,-6,-7,-8,-9,-10};
  double array_set3_x[8]={0,1,10,100,1000,10000,100000,1000000};
  double array_set4_x[6]={1,0.1,0.01,0.001,0.0001,0.00001};

  //create arrays and store and compute each y correspondingly to the cases
  double array_set1_y[11];
  create_y_array(array_set1_x,array_set1_y,11,slope,intercept);

  double array_set2_y[11];
  create_y_array(array_set2_x,array_set2_y,11,slope,intercept);

  double array_set3_y[8];
  create_y_array(array_set3_x,array_set3_y,8,slope,intercept);

  double array_set4_y[6];
  create_y_array(array_set4_x,array_set4_y,6,slope,intercept);

  //finds size of the inputed x values and creats array for the x and y's
  int size;
  fscanf(ifp,"%d\n", &size);
  double array_x[size];
  double array_y[size];
  for(int i=0;i<size;i++)
  {
    fscanf(ifp,"%lf\n", &array_x[i]);
  }
  create_y_array(array_x,array_y,size,slope,intercept);


  //print all results
  fprintf(ofp,"Your cords for set 1, X's going up by 1,0-10:\n");
  print_cords(array_set1_x,array_set1_y,11,ofp);
  fprintf(ofp,"Your cords for set 2, X's going down by 1,0--10:\n");
  print_cords(array_set2_x,array_set2_y,11,ofp);
  fprintf(ofp,"Your cords for set 3, X's multiplying by 10,0-1mil:\n");
  print_cords(array_set3_x,array_set3_y,8,ofp);
  fprintf(ofp,"Your cords for set 4, X's dividing by 10, 1-0.00001:\n");
  print_cords(array_set4_x,array_set4_y,6,ofp);
  fprintf(ofp,"Your %d cords from the X's in the input file:\n",size);
  print_cords(array_x,array_y,size,ofp);


  fclose(ifp);
  fclose(ofp);
}