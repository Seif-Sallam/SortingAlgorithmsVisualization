#include "BubbleSort.h"
#include <iostream>

BubbleSort::BubbleSort(std::vector<int> &vec)
    : Algorithm(vec)
{
    name = "Bubble Sort";
}

void BubbleSort::SolveStep()
{
    if (i < values.size() - 1)
    {
        if (values[j] > values[j + 1])
        {
            std::swap(values[j], values[j + 1]);
            lastChangeIndex1 = j;
            lastChangeIndex2 = j + 1;
        }
        j++;
        if (j >= values.size() - i - 1)
        {
            i++;
            j = 0;
        }
    }
}

bool BubbleSort::Finished()
{
    return (i >= values.size());
}

void BubbleSort::Reset()
{
    this->i = 0;
}