#include "SelectionSort.h"
#include <algorithm>

SelectionSort::SelectionSort(std::vector<int> &vec)
    : Algorithm(vec)
{
    name = "Selection Sort";
    i = 0;
}

void SelectionSort::SolveStep()
{
    if (!Finished())
    {
        int minIndex = i;
        for (int j = i + 1; j < values.size(); j++)
            if (values[j] < values[minIndex])
                minIndex = j;

        std::swap(values[i], values[minIndex]);
        lastChangeIndex1 = i;
        lastChangeIndex2 = minIndex;

        i++;
    }
}

bool SelectionSort::Finished()
{
    return i >= (values.size() - 1);
}

void SelectionSort::Reset()
{
    i = 0;
}
