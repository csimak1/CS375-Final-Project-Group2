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

int swapCounter;

void print_array(vector<int> &array)
{
    for (int i = 0; i < array.size(); i++)
    {
        cout << array[i] << " ";
    }
    cout << '\n';
}
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
        swapCounter++;
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

void heapSort(vector<int> &array, int print)
{
    build_heap(array);
    if(print == 1){
            cout << "After build-max heap: "; 
            print_array(array);
        }
    int size = array.size();
    for (int i = array.size() - 1; i >= 1; i--)
    {
        swap(array[0], array[i]);
        swapCounter++;
        size -= 1;
        heapify(array, 0, size);
        if(print == 1){
            cout << "After swap and heapify: "; 
            print_array(array);
        }
    }
}


int partition_lomuto(vector<int> &array, int low, int high, bool randomPivot)
{
    if (randomPivot == true)
    {
        int random = low + (rand() % (high - low + 1));
        swap(array[random], array[high]);
        swapCounter++;
    }
    int pivot = array[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            swap(array[i], array[j]);
            swapCounter++;
        }
    }
    swap(array[i + 1], array[high]);
    swapCounter++;
    return (i + 1);
}

int partition_hoare(vector<int> &array, int low, int high, bool randomPivot)
{
    if (randomPivot == true)
    {
        int random = low + (rand() % (high - low + 1));
        swap(array[random], array[low]);
        swapCounter++;
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
        swapCounter++;
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

int getMax(int array[], int n)
{
    int max = array[0];
    for (int i = 1; i < n; i++)
        if (array[i] > max)
            max = array[i];
    return max;
}

void countingSort(int array[], int size, int div)
{
    const int max = 10;
    int output[size];
    int count[max];

    for (int i = 0; i < max; ++i)
        count[i] = 0;

    for (int i = 0; i < size; i++)
        count[(array[i] / div) % 10]++;

    for (int i = 1; i < max; i++)
        count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; i--)
    {
        output[count[(array[i] / div) % 10] - 1] = array[i];
        count[(array[i] / div) % 10]--;
    }

    for (int i = 0; i < size; i++)
        array[i] = output[i];
}

void radixsort(int array[], int size)
{
    int max = getMax(array, size);

    for (int div = 1; max / div > 0; div *= 10)
        countingSort(array, size, div);
}

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
    vector<int> heap_test = num_generator.make_data(8, "randomRadix");
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
    heapSort(heap_test,1);
    cout << "After HeapSort: ";
    print_array(heap_test);
    cout << endl;
    cout << "--------HOARES CORRECTNESS DEMO-------" << endl;
    // HOARES DEMO
    cout << "Before Randomized Quicksort with Hoares Partition: ";
    print_array(hoares_test);
    quickSort(hoares_test, 0, hoares_test.size() - 1, true, true);
    cout << "After HeapSort: ";
    print_array(hoares_test);
    cout << endl;
    cout << "--------LOMUTO CORRECTNESS DEMO-------" << endl;
    // LOMUTO DEMO
    cout << "Before Randomized Quicksort with Lomuto Partition: ";
    print_array(lomuto_test);
    quickSort(lomuto_test, 0, lomuto_test.size() - 1, true, false);
    cout << "After Randomized Quicksort with Lomuto Partition: ";
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
    // sizes 2^10 -- 2^20
    int exponent = 10;
    int long long array_sizes[11] = {1024, 2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288, 1048576};
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
        swapCounter = 0;
        heapSort(arr,0);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diff = end - start;
        cout << "Heapsort took : " << (diff.count()) << " ms" << endl;
        cout << "Heapsort performed " << swapCounter << " swaps" << endl;
        // hoares
        auto start_hoares = chrono::high_resolution_clock::now();
        swapCounter = 0;
        quickSort(arr_hoares, 0, arr_hoares.size() - 1, true, true);
        auto end_hoares = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diff_hoares = end_hoares - start_hoares;
        cout << "Randomized Quicksort with hoares took : " << (diff_hoares.count()) << " ms" << endl;
        cout << "Randomized Quicksort with hoares performed " << swapCounter << " swaps" << endl;
        // larmuto
        auto start_lomuto = chrono::high_resolution_clock::now();
        swapCounter = 0;
        quickSort(arr_lomuto, 0, arr_lomuto.size() - 1, true, false);
        auto end_lomuto = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diff_lomuto = end_lomuto - start_lomuto;
        cout << "Randomized Quicksort with lomuto took : " << (diff_lomuto.count()) << " ms" << endl;
        cout << "Randomized Quicksort with lomuto performed " << swapCounter << " swaps" << endl;
        // Radix
        int *array = &arr_radix[0];
        int n = arr_radix.size();
        auto start_radix = chrono::high_resolution_clock::now();
        radixsort(array, n);
        auto end_radix = chrono::high_resolution_clock::now();
        chrono::duration<double, milli> diff_radix = end_radix - start_radix;
        cout << "Radix Sort took : " << (diff_radix.count()) << " ms" << endl;
        exponent += 1;
    }
    cout << "---------------------------------" << endl
         << endl;
    exponent = 10;
    // QUICKSORT RANDOM VS SORTED TESTS -------------------------------------------------------- 

    cout << "Randomized Quicksort (Hoares) with Random Order vs with Reversed Order Input Arrays: " << endl;
    cout << "-------------------------------------" << endl;
    for(int i = 0; i < 11; i++){
    // testing arrays
    vector<int> random_test = num_generator.make_data(array_sizes[i], "random");
    vector<int> reverse_test = num_generator.make_data(array_sizes[i], "reverse");
    // random
    auto start_random = chrono::high_resolution_clock::now();
    quickSort(random_test, 0, random_test.size() - 1, true, true);
    auto end_random = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> diff_random = end_random - start_random;
    cout << "Randomized Quicksort with Random input size  " << array_sizes[i] << " (2^" << exponent << ")" <<  " took : " <<  (diff_random.count()) << " ms" << endl;
    // reversely sorted
    auto start_reverse = chrono::high_resolution_clock::now();
    quickSort(reverse_test, 0, reverse_test.size() - 1, true, true);
    auto end_reverse = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> diff_reverse = end_reverse - start_reverse;
    cout << "Randomized Quicksort with Reversed input size  " << array_sizes[i] << " (2^" << exponent << ")" <<  " took : " <<  (diff_reverse.count()) << " ms" << endl << endl;
    exponent += 1;
    }
    // ------------------------------------------------------------------------
    exponent = 10;
    // radix testing
    cout << "Radix Sort with Large array values vs Smaller array values : " << endl;
    cout << "-------------------------------------" << endl;
    for(int i = 0; i < 11; i++){
    vector<int> small = num_generator.make_data(array_sizes[i], "randomRadix");
    vector<int> large = num_generator.make_data(array_sizes[i], "highValue");
    // small input
    int *array = &small[0];
    int n = small.size();
    auto start_small = chrono::high_resolution_clock::now();
    radixsort(array, n);
    auto end_small = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> diff_small = end_small - start_small;
     cout << "Radix Sort with smaller element size  " << array_sizes[i] << " (2^" << exponent << ")" << " took : " << (diff_small.count()) << " ms" << endl;
    // large input
    array = &large[0];
    n = large.size();
    auto start_large = chrono::high_resolution_clock::now();
    radixsort(array, n);
    auto end_large = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> diff_large = end_large - start_large;
    cout << "Radix Sort with large element size  " << array_sizes[i] << " (2^" << exponent << ")" << " took : " << (diff_large.count()) << " ms" << endl << endl;
    exponent += 1;
    }
    return 0;
}