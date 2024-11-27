/*Suzanne Abdullah, 400535629, 26-11-2024*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "clean.h"

/**clean_impute func:
    inputs: numrows,numcols, data array
    returns: cleaned data array
**/
float (*clean_impute(int numrows, int numcols, float data[numrows][numcols]))[2]{
    float (*newdata)[numcols] = malloc(numrows*numcols*sizeof(float)); //allocates memory for newdata array
    float avgc[numcols]; //initializes array for storing averages of column values
    int n[numcols]; //initializes array for storing count of column entries that are valid numbers
    float sum[numcols]; //initializes array for storing sum of entries in each column
    
    if (newdata == NULL){
        return NULL;
    }

    //for loop sets all array values to zero by default
    for (int i=0; i<numcols; i++){
        sum[i] = 0;
        avgc[i] = 0;
        n[i] = 0;
    }

    //for loop adds appropriate sum values to array, and updates count variables at the same time
    for (int i=0; i<numrows; i++){
        for (int j=0; j<numcols; j++){
            if (!isnan(data[i][j])){
                sum[j] = sum[j] + data[i][j];
                n[j]++;
            }
        }
    }

    //for loop calculates average for each column using sum and n arrays and adds to appropriate array index
    for (int i=0; i<numcols; i++){
        if (n[i]>0) {
            avgc[i] = sum[i]/n[i];
        }
    }

    //for loop checks if float is an nan value, and if so, replaces with the corresponding average value for that column
    for (int i=0; i<numrows; i++){  
        for(int j=0; j<numcols; j++){
            if (isnan(data[i][j])){
                newdata[i][j] = avgc[j];
            }
            else{ //if float is valid, it's added to the new array
                newdata[i][j] = data[i][j];
            }
        }
    }

    return (newdata);
}

/** output_data func:
    inputs: numrows, numcols, data array
    returns: nothing - prints cleaned data to stdout
**/
void output_data(int numrows,int numcols,float data[numrows][numcols]){
    //first prints numrows and numcols 
    printf("%d %d\n",numrows,numcols);
    
    //for loop prints out each entry in array rounded to 3 decimal places
    for (int i=0; i<numrows; i++){
        for (int j=0; j<numcols; j++){
            printf("%.3f ", data[i][j]);
        }
        printf("\n"); //creates line break before each new row
    }

}