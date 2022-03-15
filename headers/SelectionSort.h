#pragma once
#include "Algorithm.h"

class SelectionSort : public Algorithm
{
public:
    SelectionSort(std::vector<int> &vec);

    void SolveStep() override final;
    bool Finished() override final;
    void Reset() override final;

private:
    int i;
};