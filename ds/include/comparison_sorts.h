int BubbleSort(int *array, size_t len);
int SelectionSort(int *array, size_t len);
int InsertionSort(int *array, size_t len);
/* -------------------------------------------------------------------------- *
 * Description - search for the given number.
 * Arguments - int to be found, int array to search in.
 * Return - returns 1 if found,0 otherwise.
 * Time Complexity - O(log(n)).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
int IterativeSearch(int n ,int arr[], int len);
/* -------------------------------------------------------------------------- *
 * Description - search for the given number.
 * Arguments - int to be found, int array to search in.
 * Return - returns 1 if found,0 otherwise.
 * Time Complexity - O(log(n)).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
int RecursiveSearch(int n ,int arr[], int len);



/* -------------------------------------------------------------------------- *
 * Description - sorting the array.
 * Arguments - int to be found, int array to search in.
 * Return - void 
 * Time Complexity - O(nlog(n)).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- */
void MergeSort(int *arr_to_sort, size_t num_elements);


/* -------------------------------------------------------------------------- *
 * Description - sorting the array.
 * Arguments - int to be found, int array to search in.
 * Return - void 
 * Time Complexity - O(nlog(n)).
 * Space Complexity - O(1).
 * -------------------------------------------------------------------------- 
 *
 */

void QuickSort(int arr[], size_t length);