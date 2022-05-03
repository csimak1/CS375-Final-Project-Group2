#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
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
void print_heap(vector<int> &array)
{
    for (int i = 0; i < array.size(); i++)
    {
        cout << array[i] << " ";
    }
    cout << '\n';
}

int partition_lomuto(vector<int> &array, int low, int high, bool randomPivot){
    if(randomPivot == true){
        int random = low + (rand() % (high - low + 1));
        swap(array[random], array[high]);
    }
    int pivot = array[high];
    int i = (low - 1);
    for(int j = low; j <= high - 1; j++){
        if(array[j] <= pivot){
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[i+1], array[high]);
    return (i+1);
}

int partition_hoare(vector<int> &array, int low, int high, bool randomPivot){
    if(randomPivot == true){
        int random = low + (rand() % (high - low + 1));
        swap(array[random], array[low]);
    }
    int pivot = array[low];
    int i = low - 1;
    int j = high + 1;

    while (true){
        do{
            i++;
        } while (array[i] < pivot);

        do{
            j--;
        } while(array[j] > pivot);

        if(i >= j){
            return j;
        }

        swap(array[i], array[j]);
    }
}

void quickSort(vector<int> &array, int low, int high, bool randomPivot, bool hoare){
    if (low < high){
        int pi;
        if(hoare == false){
            pi = partition_lomuto(array, low, high, randomPivot);
            quickSort(array, low, pi - 1, randomPivot, hoare);
            quickSort(array, pi + 1, high, randomPivot, hoare);
        }
        else{
            pi = partition_hoare(array, low, high, randomPivot);
            quickSort(array, low, pi, randomPivot, hoare);
            quickSort(array, pi + 1, high, randomPivot, hoare);
        }

        
        
    }
}

int main(int argc, char *argv[])
{
    NumGen heap_generator("heap");
    vector<int> arr = heap_generator.make_data(100, "heap");
    //heapSort(arr);
    quickSort(arr, 0, arr.size() - 1, true, true);
    print_heap(arr);


    return 0;
}