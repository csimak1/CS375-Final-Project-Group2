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

int main(int argc, char *argv[])
{
    NumGen heap_generator("heap");
    vector<int> arr = heap_generator.make_data(100, "heap");
    heapSort(arr);
    print_heap(arr);

    return 0;
}