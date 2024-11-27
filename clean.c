/*Suzanne Abdullah, 400535629, 26-11-2024*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "clean.h"

int numrows;
int numcols;

/**read_data func:
    inputs: none
    returns: data array
**/
float (*read_data(void))[2]{
    //scans first two numbers from standard input to get number of rows and columns respectively
    scanf("%d", &numrows);
    scanf("%d", &numcols);

    //allocates memory for data array
    float (*data)[numcols] = malloc(numrows*numcols*sizeof(float));
    if (data == NULL){
        return NULL;
    }

    //for loop scans each item as a float and adds to array
    for (int i = 0; i < numrows; i++){
        for (int j = 0; j < numcols; j++){
                scanf("%f", &data[i][j]);
        }
    }

    return (data);
}

/**clean_delete func:
    inputs: data array
    returns: cleaned data array
**/
float (*clean_delete(float data[numrows][numcols]))[2]{
    //allocating memory for newdata array
    float (*newdata)[numcols] = malloc(numrows*numcols*sizeof(float));
    if (newdata == NULL){
        return NULL;
    }

    int rowd[numrows]; //rowd array stores index of rows that should be deleted
    int new_row = 0; //used to represent the new row count

    //for loop checks to see if floats are nan values, if so adds a one to the corresponding index of rowd[]
    for (int i=0; i<numrows; i++){  
        for(int j=0; j<numcols; j++){
            if (isnan(data[i][j])){
                rowd[i] = 1;
                break;
            }
        }
    }

    //for loop adds all rows without an nan value present in them to the new array
    for (int i=0; i<numrows; i++){
        if (rowd[i] != 1){ //checks if row contains nan
            for (int j=0; j<numcols; j++){
                newdata[new_row][j] = data[i][j];
            }
            new_row++;
        }
    }
    
    //reallocates memory for newdata array to compensate for unused rows
    newdata = realloc(newdata,new_row*sizeof(*newdata));
    numrows = new_row; //reassigns numrows variable to new row number
    return (newdata); //returns new data
}

/**main func:
    inputs: argc, argv
    returns: 0, prints cleaned data to stdout
**/
void main(int argc, char *argv[]){
    float (*data)[numcols] = read_data(); //stores input data in an array
    float (*newdata)[numcols]; //initializes clean data array

    //checks if more than one argument was used
    if (argc>1){
        if (strcmp(argv[1],"-d") == 0){ //checks if d flag was used, if so uses delete strategy
            newdata = clean_delete(data);
        }
        
        else { //else: uses impute strategy
            newdata = clean_impute(numrows,numcols,data);
        }
    }

    else{
        newdata = clean_impute(numrows,numcols,data);
    }

    //finally - prints using output data
    output_data(numrows,numcols,newdata);

    //frees data allocated with malloc
    free(data);
    free(newdata);
}