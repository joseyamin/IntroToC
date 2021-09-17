/*
 *  UCF COP2332 Fall 2020 Assignment Solution
 *  Copyright 2020 Jose Yamin
 */

//this code has a structure instance gets the data from the input and prints all the instance structures into a bin folder then finally prints all of it into the console from the bin folder.
#include <stdio.h>

//the structure that holds the data such as the title equation xs and ys
struct instance_struct {
    char title[64];
    float m;
    float b;
    double x[10];
    double y[10];
};

//naming the structure only instance 
typedef struct instance_struct instance;

//the print function given to us that prints the instance neatly into console
void instance_print(instance *is) {
    int i;

    printf("\nInstance: %s\n", is->title);
    printf("  y = %lf x + %lf\n", is->m, is->b);

    for(i = 0; i < 10; i = i + 1) {
        printf("  x: %lf   y: %lf\n", is->x[i], is->y[i]);
    }
}

//gets the instance pointer but computes the y array according to the x array
void set_y_array(instance *is){
  for(int i=0;i<10;i++){
    is->y[i]=(is->m*is->x[i])+is->b;
  }
}

//retrives data from the input file and sets it into the structure fields, calls the set_y_array funtion to compute ys and finally writes the structure into a bin file
void create_instance(FILE *ifp,FILE *ofp,instance *is){
  fgets(is->title,63,ifp);
  fscanf(ifp,"%f %f\n",&(is->m),&(is->b));
  fscanf(ifp,"%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",&(is->x[0]),&(is->x[1]),&(is->x[2]),&(is->x[3]),&(is->x[4]),&(is->x[5]),&(is->x[6]),&(is->x[7]),&(is->x[8]),&(is->x[9]));


  //for(int i=0;i<10;i++){
  //  fscanf(ifp,"%lf ",is->x);
  //}
  //fscanf(ifp,"\n");

  set_y_array(is);
  fwrite(is,sizeof(instance),1,ofp);
}

int main(void) {
  //files
    FILE *ifp, *ofp;
    ifp=fopen("as4input.txt","r");
    ofp=fopen("as4output-yamin-jose.bin", "wb");

//the first int in the file is the amount of times a structure is given
    int count;
    fscanf(ifp,"%d\n",&count);
    instance is;

//loop that goes the amount of times for each structure and calls the function create_instance which creates and prints structure to bin file
    for(int i=0;i<count;i++){
      create_instance(ifp,ofp,&is);
    }

    //close files
    fclose(ofp);
    fclose(ifp);

    //opens the bin file in read mode to read file the file is not at the end if reading the next data size of instance is an instance structure then call the print function to print it into console
    ofp = fopen("as4output-yamin-jose.bin", "rb");
    while(!feof(ifp)) {
        if(fread(&is, sizeof(instance), 1, ifp)) {
            instance_print(&is);
        }
    }
    fclose(ofp);
}