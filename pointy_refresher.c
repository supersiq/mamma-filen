#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int main(){

    const int size = 3;
    int a[size];
    int min, max;
    for(int i = 0; i<size; i++){
        printf("enter # to place in index [%d]", a[i]);
        scanf("%d", &a[i]);
    }
    
    int r = rand() % 100;
    for(int i = 0; i < size; i++){
        printf("rand:# = %d, %d ", r, a[i]);

    } 
    return 0;
}