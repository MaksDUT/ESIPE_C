#ifndef __ARRAY__
#define __ARRAY__

/* Allocate memory for an array which can contain `size`
   integers. The returned C array has memory for an extra last
   integer labelling the end of the array. 
*/
int *allocate_integer_array(int size);
/* Free an integer array */
void free_integer_array(int *tab);
/* Return the size of the array*/
int array_size(int *array);
/* Print the array*/
void print_array(int *array);
/* Compares if two tables are equal*/
int are_arrays_equal(int *first, int *second);
/* Copies the array as an argument into a new array returns the new array*/
int *copy_array(int *array);
/* Asks the user for the size of the array (size) and then to enter positive values to fill the array.*/
int *fill_array(void);
/* Create an array of size i with random values (max size : max_entry)*/
int *random_array(int size, int max_entry);
/* Concatenate two array into one*/
int *concat_array(int *first, int *second);
/*Returns a sorted array whose entries are exactly those of the two arrays in the argument. These two arrays in argument are supposed to be already sorted.*/
int *merge_sorted_arrays(int *first, int *second);
/*construct two arrays (which will be placed in the pointers) each containing half of the elements of the first two array*/
void split_arrays(int *array, int **first, int **second);
/*This use the merge sort algorithm. returns a new sorted array containing the same elements as the array as argument.*/
int *merge_sort(int *array);

#endif