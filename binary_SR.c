#include <stdio.h> // standard c library header
#include <stdlib.h>// c header file that contains functions as malloc, rand srand
#include <time.h> // c library for time functions

//Declaring functions
/////////////////////////////////////////////////////

void random_array(long int n, long int a[]); // fuction to generate random numbers in an array
void print_array(long int n, long int a[]); // function to print the array in columns
int cmpfunc(const void * a, const void * b); // function to auxiliate the qsort function, standard c library for the quick sort algorithm
long int binarySearchR(long int x, long int low, long int upp, long int a[]); // functions that contains the searching algorithm with the recursive aproach

/////////////////////////////////////////////////////

int main(int argc, char const *argv[]) {
  int k; // represents the power of 10, and this will be the size of the array
  long int n;// n --> the size of the array
  clock_t t_start1,t_start2,t_end1,t_end2; // variables to measure the time passed to sort the array
  double timeUsed1,timeUsed2;
  for (k = 2; k <= 6; k++) {

    n = 1;
    int i = k;
    while (i >= 0){
      n = n*10;
      i--;
    }

    long int *a = (long int *)malloc(n*sizeof(long int ));
    if (a == NULL) {
      printf("Memory could not be allocated" );
      exit(EXIT_FAILURE); // in this case, we have a problem in the process of allocating memory for the array
    }else{
      random_array(n,a);
      //print_array(n,a);
      printf("K = %d\n", k );

      t_start1 = clock();
      qsort(a,n,sizeof(long int),cmpfunc);// we will use the C standard function for quick sort to sort the input array, and then allow us to test the binary search algorithm
      t_end1 = clock();
      //print_array(n,a);

      long int b;
      t_start2 = clock();
      b = binarySearchR(95,0,n,a);
      t_end2 = clock();
      if (b == -1){
        printf("The element doesen't belong to the array !!\n");
      }else {
        printf("Value Found\n");
        printf("b = %ld\n", b );
      }
      timeUsed1 = ((double)(t_end1 - t_start1))/CLOCKS_PER_SEC;
      printf("Time passed for sorting : %f \n", timeUsed1);
      timeUsed2 = ((double)(t_end2 - t_start2))/CLOCKS_PER_SEC;
      printf("Time passed for searching : %f \n", timeUsed2);
      printf("Total time : %f \n",(timeUsed1 + timeUsed2) );

      free(a);
    }
  }
  return 0;
}

//FUNCTIONS
/////////////////////////////////////////////////////

void random_array(long int n, long int a[]){
  // n is the number of elements of the array
  srand(time(NULL));
  long int i;
  for (i = 0; i < n; i++) { // loop to fill the array
    a[i] = rand() % n;
    //this generates a set of random numbers in the range 0 to n
  }
}

/////////////////////////////////////////////////////

void print_array(long int n, long int a[]){
  printf("Printing the array : \n" );
  long int i;
  int count = 0; // to count the number of columns in each row
  for ( i = 0; i < n; i++) {
    printf("a[%ld] = %ld ",i,a[i] );
    count += 1;
    if (count == 10){ // print the array in 10 columns
      printf("\n"); // new row
      count = 0; // return to count
    }
  }
}

/////////////////////////////////////////////////////

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

/////////////////////////////////////////////////////

long int binarySearchR(long int x, long int low, long int upp, long int a[]){// x --> is the element we are looking for, a[] --> the array that could contain or not the element
  //low -> lower limit of the input range
  // upp --> upper limit
  long int mean; // the mean value among the index positions
  if (low <= upp) {
    mean = (long int)(upp + low)/2;
    //First we need to check if the algorithm find the right value
    if (x == a[mean]) {
      printf("The position of the element is = %ld\n", mean );
      return x; // the algorithm find the element
    }else if (a[mean] > x) {
      // At this point, if the mean value is greater than the number we are looking for, the correct position must be to the left of its position
      return binarySearchR(x, low, mean - 1,a);
    }else{
      // the mean value is less than the number we are looking for, therefore, the correct position must be on the right of its position
      return binarySearchR(x,mean + 1, upp,a);
    }
  }
  return -1;
}
