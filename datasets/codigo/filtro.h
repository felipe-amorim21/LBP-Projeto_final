#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int getElement(unsigned char *, int , int , int );
int *getNeighbors(unsigned char *, int , int , int , int neighbors[8], int binary[8]);
int getDecimal(int binary[8]);
void matrizDecimal(int *, int , int , int *);