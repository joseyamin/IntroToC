/*
 *  UCF COP2332 Fall 2020 Assignment Solution
 *  Copyright 2020 Jose Yamin
 */

//program grabs slope intercept and x points and computes the ys from the input and puts all the data into the struct coord and prints it all.
#include <stdio.h>
#include <stdlib.h>
//coord struct
struct coord_struct{
  float m,b;
  int count;
  double *x,*y;
};
typedef struct coord_struct coord_struct;
//coord constructor
coord_struct *new_coord(float m,float b, int count, double *x, double *y){

  coord_struct *coord=malloc(sizeof(coord_struct));
  coord->m=m;
  coord->b=b;
  coord->count=count;
  coord->x=x;
  coord->y=y;
  return coord;
}
//coord destructor
void dispose_coord_struct(coord_struct *coord){
  free(coord);
}
//coord printer to ofp
void output_coord_struct(coord_struct *coord, FILE *ofp){
  fprintf(ofp,"Slope:%f\n",coord->m);
  fprintf(ofp,"Intercept:%f\n",coord->b);
  for(int i=0;i<coord->count;i++){
    fprintf(ofp,"X%d=%lf Y%d=%lf\n",i+1,coord->x[i],i+1,coord->y[i]);
  }
}
//get m b and x and compute and return y
double compute_y(float m,float b,double x){
  return m*x+b;
}
int main(void) {
  //open files
  FILE *ifp=fopen("as5input.txt","r");
  FILE *ofp=fopen("as5output-yamin-jose.txt","w");
  //gets info from ifp for m b and count
  float m,b;
  int count;
  fscanf(ifp,"%f %f\n",&(m),&(b));
  fscanf(ifp,"%d\n",&(count));
  //allocates space to store count amount of x and y
  double *x=malloc(sizeof(double)*count);
  double *y=malloc(sizeof(double)*count);
  //sets all xs and computes ys and sets them as well
  for(int i=0;i<count;i++){
    fscanf(ifp,"%lf ",&x[i]);
    y[i]=compute_y(m,b,x[i]);
  }
  //creats the coord
  coord_struct *coord=new_coord(m, b,count,x,y);
  //outputs the coord
  output_coord_struct(coord, ofp);
  //frees and closes everything
  free(x);
  free(y);
  fclose(ofp);
  fclose(ifp);
}