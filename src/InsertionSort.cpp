#include "InsertionSort.h"
InsertionSort::InsertionSort(std::vector<int> &vec)
    : Algorithm(vec)
{
    name = "Insertion Sort";
}

void InsertionSort::SolveStep()
{
    if (i < values.size())
    {
        key = values[i];
        int j = i - 1;
        while (j >= 0 && values[j] > key)
        {
            values[j + 1] = values[j];
            j--;
        }
        values[j + 1] = key;
        lastChangeIndex1 = i;
        lastChangeIndex2 = j + 1;
        i++;
    }
}

bool InsertionSort::Finished()
{
    return i == values.size();
}

void InsertionSort::Reset()
{
    key = -1;
    i = 1;
}
