#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array
{
  int capacity;    // How many elements can this array hold?
  int count;       // How many states does the array currently hold?
  char **elements; // The string elements contained in the array
} Array;

/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array(int capacity)
{
  // Allocate memory for the Array struct
  Array *arr = malloc(sizeof(Array));
  // Set initial values for capacity and count
  arr->capacity = capacity;
  arr->count = 0;
  // Allocate memory for elements
  arr->elements = malloc(capacity * sizeof(char *)); // Actually stores the pointers, not the char themselves.
  return arr;
}

/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr)
{

  // Free all elements
  for (int i = 0; i < arr->count; i++)
  {
    free(arr->elements[i]);
  }
  // Free array
  free(arr);
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr)
{

  // Create a new element storage with double capacity
  char **new_ptr = malloc(arr->capacity * 2 * sizeof(char *));
  // Copy elements into the new storage
  for (int i = 0; i < arr->count; i++)
  {
    new_ptr[i] = arr->elements[i];
  }
  // Free the old elements array (but NOT the strings they point to)
  free(arr->elements);
  // Update the elements and capacity to new values
  arr->elements = new_ptr;
  arr->capacity += arr->capacity;
}

/************************************
 *
 *   ARRAY FUNCTIONS
 *
 ************************************/

/*****
 * Return the element in the array at the given index.
 *
 * Throw an error if the index is out of range.
 *****/
char *arr_read(Array *arr, int index)
{

  // Throw an error if the index is greater or equal to than the current count
  if (index >= arr->count)
  {
    printf("Requested index out of range.");
    return NULL;
  }
  else
  {
    // Otherwise, return the element at the given index
    return arr->elements[index];
  }
}

/*****
 * Insert an element to the array at the given index
 *
 * Store the VALUE of the given string, not the REFERENCE
 *****/
void arr_insert(Array *arr, char *element, int index)
{

  // Throw an error if the index is greater than the current count
  if (index > arr->count)
  {
    printf("Requested index to insert is out of range.");
  }
  else
  {
    // Resize the array if the number of elements is over capacity
    if (arr->count == arr->capacity)
    {
      printf("Resizing...\n");
      resize_array(arr);
    }
    // Move every element after the insert index to the right one position
    for (int i = arr->count - 1; i > index; i--)
    {
      printf("Shift Right");
      char *temp = strdup(arr->elements[i + 1]);
      printf("%s\n", temp);
      arr->elements[i] = temp;
    }
    // Copy the element (hint: use `strdup()`) and add it to the array
    char *copied_element = strdup(element);
    arr->elements[index] = copied_element;
    // Increment count by 1
    arr->count++;
  }
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element)
{

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  if (arr->count == arr->capacity)
  {
    printf("Capacity: %d, Resizing...\n", arr->capacity);
    resize_array(arr);
  }
  // Copy the element and add it to the end of the array
  char *copied_element = strdup(element);
  arr->elements[arr->count] = copied_element;
  // Increment count by 1
  arr->count++;
}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element)
{

  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!
  int found_index = -1;
  for (int i = 0; i < arr->count; i++)
  {
    if (found_index != -1)  
    {
      arr->elements[i-1] = arr->elements[i]; // Shift over every element after the removed element to the left one position
    }
    else
    {
      if (strcmp(arr->elements[i],element) == 0)
      {
        free(arr->elements[i]);
        found_index = i;
        printf("Found Index: %d\n", found_index);
      }
    }
  }

  // Decrement count by 1
  arr->count--;
}

/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr)
{
  printf("Capacity: %d, ", arr->capacity);
  printf("Count: %d, ", arr->count);
  printf("[");
  for (int i = 0; i < arr->count; i++)
  {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1)
    {
      printf(",");
    }
  }
  printf("]\n");
}

#ifndef TESTING
int main(void)
{

  Array *arr = create_array(1);

  // arr_insert(arr, "STRING1", 0);
  // arr_print(arr);
  // resize_array(arr);
  // arr_print(arr);

  arr_append(arr, "STRING3");
  arr_append(arr, "STRING4");
  arr_append(arr, "STRING5");
  arr_print(arr);
  // arr_insert(arr, "STRING2", 0);
  // arr_print(arr);
  // arr_insert(arr, "STRING3", 0);
  // arr_print(arr);
  // arr_insert(arr, "STRING4", 0);
  // arr_print(arr);
  arr_remove(arr, "STRING4");
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
