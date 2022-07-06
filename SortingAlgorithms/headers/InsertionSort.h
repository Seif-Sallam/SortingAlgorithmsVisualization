#pragma once
#include <iostream>
#include "Algorithm.h"

class InsertionSort : Algorithm
{
public:
    InsertionSort(std::vector<int> &vec);

    void SolveStep() override final;
    bool Finished() override final;
    void Reset() override final;

private:
    int key;
    int i = 1;
};