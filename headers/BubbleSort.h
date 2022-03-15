#pragma once
#include "Algorithm.h"

class BubbleSort : Algorithm
{
public:
    BubbleSort(std::vector<int> &vec);

    void SolveStep() override final;
    bool Finished() override final;
    void Reset() override final;

private:
    int i = 0;
    int j = 0;
};