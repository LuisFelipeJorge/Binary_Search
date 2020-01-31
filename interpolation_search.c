#include <stdio.h> // standard c library header
#include <stdlib.h>// c header file that contains functions as malloc, rand srand
#include <time.h> // c library for time functions

//Declaring functions
/////////////////////////////////////////////////////

void random_array(long int n, long int a[]); // fuction to generate random numbers in an array
void print_array(long int n, long int a[]); // function to print the array in columns
int cmpfunc(const void * a, const void * b); // function to auxiliate the qsort function, standard c library for the quick sort algorithm
long int interpoSearch(long int x, long int n, long int a[]);// Function that contains the searching algorithm

/////////////////////////////////////////////////////

int main(int argc, char const *argv[]) {

  long int n = 1000;
  long int *a = (long int *)malloc(n*(sizeof(long int)));
  if (a == NULL) {
    printf("Memory could not be allocated" );
    exit(EXIT_FAILURE); // in this case, we have a problem in the process of allocating memory for the array
  }else{
    random_array(n,a);
    print_array(n,a);
    qsort(a,n,sizeof(long int),cmpfunc);
    print_array(n,a);
    long int  b;
    b = interpoSearch(940,n,a);
    if (b == -1) {
      printf("The element doesen't belong to the array\n");
    }else{
      printf("Element found at the position %ld \n", b );
      printf("array[%ld] = %ld\n",b, a[b] );
    }

    free(a);
  }

  getchar();
  return 0;
}

/////////////////////////////////////////////////////

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

long int interpoSearch(long int x, long int n, long int a[]){
    // x --> the valuer we are looking for
    // n --> the size of the input array
    //a the First pointer of the array
    long int lower = 0; // lower limit of the array
    long int upper = n - 1;// upper limit
    long int pos; // auxiliar variable to help search for the right index of the element x

    //For this algorithm to work, we need to assume that the input array has already been sorted and that the numbers within the array have been uniformly distributed.
    //After that, if x belongs to the array, its index must be within the range {lower ... upper}.
    while (lower <= upper && x >= a[lower] && x <= a[upper]) {
      //  The above statement ensures that the algorithm does not fall into an infinity loop during the execution
      if (lower == upper) {
        // array of only one element
        if (a[lower] == x) {
          // the algorithm had founded the position of x
          return lower;
        }else{
          // The element doesen't belong to the input arrray
          return -1;
        }
      }
      //  looking for the position with keeping uniform distribution in mind.
      /*(position - lower)         (x - arr[lower])
        ------------------  =   -------------------------
        (upper - lower)        (arr[upper] - arr[lower])
        */
      //this formula comes from an inversely proportional relation between the distances between the indices of the elements
      // and the distance between the values ​​contained in the array.
      // the relationship between the distances of the element and the lower limit with the distance between the upper limit and the lower limit
      // is proportional to the relationship between the difference of the input value and the first value of the array with the difference between the first value and the last value of the array.
      pos = lower + (long int)((double)((x - a[lower])/(a[upper] - a[lower])));
      if (x == a[pos]) {
        // element found
        return pos;
      }else if (x > a[pos]) {
        // x is greater than the element on the index pos, therefore x must be on the right of pos
        lower = pos +1;
      }else{
        // x is less than the element on the index pos, therefore x must be on the left of pos
        upper = pos - 1;
      }
    }
    // at this moment, the element doesen't belong to the array
    return -1;
}

/////////////////////////////////////////////////////
