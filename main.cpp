#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include "NumberGenerator.h"
using namespace std;

// HeapSort
// Radix Sort
// Quiksort

void heapify(vector<int> &array, int i, int size)
{
    int largest = i;
    int right_child = 2 * i + 2;
    int left_child = 2 * i + 1;

    if ((left_child < size) && array[left_child] > array[i])
    {
        largest = left_child;
    }
    else
    {
        largest = i;
    }
    if ((right_child < size) && array[right_child] > array[largest])
    {
        largest = right_child;
    }
    if (largest != i)
    {
        swap(array[i], array[largest]);
        heapify(array, largest, size);
    }
}
void build_heap(vector<int> &array)
{
    for (int i = (array.size() / 2); i >= 0; i--)
    {
        heapify(array, i, array.size());
    }
}

void heapSort(vector<int> &array)
{
    build_heap(array);
    int size = array.size();
    for (int i = array.size() - 1; i >= 1; i--)
    {
        swap(array[0], array[i]);
        size -= 1;
        heapify(array, 0, size);
    }
}
void print_array(vector<int> &array)
{
    for (int i = 0; i < array.size(); i++)
    {
        cout << array[i] << " ";
    }
    cout << '\n';
}

int partition_lomuto(vector<int> &array, int low, int high, bool randomPivot)
{
    if (randomPivot == true)
    {
        int random = low + (rand() % (high - low + 1));
        swap(array[random], array[high]);
    }
    int pivot = array[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[high]);
    return (i + 1);
}

int partition_hoare(vector<int> &array, int low, int high, bool randomPivot)
{
    if (randomPivot == true)
    {
        int random = low + (rand() % (high - low + 1));
        swap(array[random], array[low]);
    }
    int pivot = array[low];
    int i = low - 1;
    int j = high + 1;

    while (true)
    {
        do
        {
            i++;
        } while (array[i] < pivot);

        do
        {
            j--;
        } while (array[j] > pivot);

        if (i >= j)
        {
            return j;
        }

        swap(array[i], array[j]);
    }
}

void quickSort(vector<int> &array, int low, int high, bool randomPivot, bool hoare)
{
    if (low < high)
    {
        int pi;
        if (hoare == false)
        {
            pi = partition_lomuto(array, low, high, randomPivot);
            quickSort(array, low, pi - 1, randomPivot, hoare);
            quickSort(array, pi + 1, high, randomPivot, hoare);
        }
        else
        {
            pi = partition_hoare(array, low, high, randomPivot);
            quickSort(array, low, pi, randomPivot, hoare);
            quickSort(array, pi + 1, high, randomPivot, hoare);
        }
    }
}

// *** START Radix Sort ***

// Function to get the largest element from an array
int getMax(int array[], int n)
{
    int max = array[0];
    for (int i = 1; i < n; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}

// Using counting sort to sort the elements in the basis of significant places
void countingSort(int array[], int size, int place)
{
    const int max = 10;
    int output[size];
    int count[max];

    for (int i = 0; i < max; ++i)
        count[i] = 0;

    // Calculate count of elements
    for (int i = 0; i < size; i++)
        count[(array[i] / place) % 10]++;

    // Calculate cumulative count
    for (int i = 1; i < max; i++)
        count[i] += count[i - 1];

    // Place the elements in sorted order
    for (int i = size - 1; i >= 0; i--)
    {
        output[count[(array[i] / place) % 10] - 1] = array[i];
        count[(array[i] / place) % 10]--;
    }

    for (int i = 0; i < size; i++)
        array[i] = output[i];
}

// Main function to implement radix sort
void radixsort(int array[], int size)
{
    // Get maximum element
    int max = getMax(array, size);

    // Apply counting sort to sort elements based on place value.
    for (int place = 1; max / place > 0; place *= 10)
        countingSort(array, size, place);
}

// Print an array
void printArray(int array[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << array[i] << " ";
    cout << endl;
}

// *** END Radix Sort ***
void print_correctness(NumGen num_generator)
{
    // Correctness Demo Arrays
    vector<int> heap_test = num_generator.make_data(15, "random");
    vector<int> hoares_test = num_generator.make_data(15, "random");
    vector<int> lomuto_test = num_generator.make_data(15, "random");
    vector<int> radix_test = num_generator.make_data(15, "random");
    // Tests for QuickSort and Radix
    vector<int> testReverse = num_generator.make_data(100, "reverse");
    vector<int> testhighValue = num_generator.make_data(100, "highValue");
    // HEAP DEMO
    cout << endl;
    cout << "--------HEAP CORRECTNESS DEMO-------" << endl;
    cout << "Before HeapSort: ";
    print_array(heap_test);
    heapSort(heap_test);
    cout << "After HeapSort: ";
    print_array(heap_test);
    cout << endl;
    cout << "--------HOARES CORRECTNESS DEMO-------" << endl;
    // HOARES DEMO
    cout << "Before QuickSort with Hoares Partition: ";
    print_array(hoares_test);
    quickSort(hoares_test, 0, hoares_test.size() - 1, true, true);
    cout << "After HeapSort: ";
    print_array(hoares_test);
    cout << endl;
    cout << "--------LOMUTO CORRECTNESS DEMO-------" << endl;
    // LOMUTO DEMO
    cout << "Before Quicksort with Lomuto Partition: ";
    print_array(lomuto_test);
    quickSort(lomuto_test, 0, lomuto_test.size() - 1, true, false);
    cout << "After Quicksort with Lomuto Partition: ";
    print_array(lomuto_test);
    cout << endl;
    cout << "--------RADIX CORRECTNESS DEMO -------" << endl;
    // LOMUTO DEMO
    cout << "Before Radix Sort: ";
    print_array(radix_test);
    int *array = &radix_test[0];
    int n = radix_test.size();
    radixsort(array, n);
    cout << "After Radix Sort: ";
    printArray(array, n);
    cout << "---------------" << endl;
    cout << endl;
}

int main(int argc, char *argv[])
{
    NumGen num_generator("heap");

    //-------------- ALL HEAP TESTS -------------------
    // sizes 2^15 -- 2^22
    int exponent = 10;
    int long long array_sizes[11] = {1024, 2048, 131072, 4096, 8192, 16384, 32768, 65536, 262144, 524288, 1048576};
    // Correctness tests
    print_correctness(num_generator);

    // ABOVE IS JUST TESTING GENERATOR FUNCTIONS
    cout << endl;
    cout << "Testing running time for inputs ranging from 2^10 to 2^20 " << endl;
    for (int i = 0; i < 11; i++)
    {
        cout << "---------------------------------" << endl;
        cout << "Size: " << array_sizes[i] << "(2^" << exponent << ")" << endl;
        // heapsort
        vector<int> arr = num_generator.make_data(array_sizes[i], "random");
        vector<int> arr_hoares = arr;
        vector<int> arr_lomuto = arr;
        vector<int> arr_radix = arr;

        auto start = chrono::high_resolution_clock::now();
        heapSort(arr);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diff = end - start;
        cout << "Heapsort took : " << (diff.count()  ) << " ms" << endl;
        // hoares
        auto start_hoares = chrono::high_resolution_clock::now();
        quickSort(arr_hoares, 0, arr_hoares.size() - 1, true, true);
        auto end_hoares = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diff_hoares = end_hoares - start_hoares;
        cout << "Quicksort with haores took : " << (diff_hoares.count()  ) << " ms" << endl;
        // larmuto
        auto start_lomuto = chrono::high_resolution_clock::now();
        quickSort(arr_lomuto, 0, arr_lomuto.size() - 1, true, false);
        auto end_lomuto = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diff_lomuto = end_lomuto - start_lomuto;
        cout << "Quicksort with lomuto took : " << (diff_lomuto.count()  ) << " ms" << endl;
        // Radix
        int *array = &arr_radix[0];
        int n = arr_radix.size();
        auto start_radix = chrono::high_resolution_clock::now();
        radixsort(array, n);
        auto end_radix = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diff_radix = end_radix - start_radix;
        cout << "Radix Sort took : " << (diff_radix.count()  ) << " ms" << endl;
        exponent += 1;
    }
    cout << "---------------------------------" << endl << endl;
    cout << "Quicksort (Hoares) with Random Order vs with Reversed Order Input Arrays: " << endl;
    cout <<"-------------------------------------" << endl;
    //testing arrays
    vector<int> random_test = num_generator.make_data(10000, "random");
    vector<int> reverse_test = num_generator.make_data(100000, "reverse");
    // hoares
    auto start_random = chrono::high_resolution_clock::now();
    quickSort(random_test, 0, random_test.size() - 1, true, true);
    auto end_random = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> diff_random = end_random - start_random;
    cout << "Quicksort with Random took : " << (diff_random.count()  ) << " ms" << endl;
    // larmuto
    auto start_reverse = chrono::high_resolution_clock::now();
    quickSort(reverse_test, 0, reverse_test.size() - 1, true, true);
    auto end_reverse = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> diff_reverse = end_reverse - start_reverse;
    cout << "Quicksort with Reverse took : " << (diff_reverse.count()  ) << " ms" << endl << endl << endl;

    return 0;
}