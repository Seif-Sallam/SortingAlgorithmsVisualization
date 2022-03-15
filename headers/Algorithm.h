#pragma once
#include <vector>
#include <string>
class Algorithm
{
public:
    inline Algorithm(std::vector<int> &vec) : values(vec) {}

    virtual void SolveStep() = 0;
    virtual bool Finished() = 0;
    virtual void Reset() = 0;
    std::string name;
    int lastChangeIndex1, lastChangeIndex2;

protected:
    std::vector<int> &values;
};