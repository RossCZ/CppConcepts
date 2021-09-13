#include "stdafx.h"
#include "MoveSemantics.h"

#include <iostream>
#include <vector>
#include <chrono>
#include <string>


struct Ant
{
    int legs;
    int arms;
    double value;
    std::string name;
};

class SetCreator
{
public:
    std::vector<Ant> createSet(int noAnts)
    {
        std::vector<Ant> mySet;
        for (int i = 0; i < noAnts; i++)
        {
            Ant ant;
            ant.legs = i;
            ant.arms = i * 2;
            mySet.push_back(ant);
        }
        analyzeSet(mySet);

        return mySet;
    }

    void analyzeSet(const std::vector<Ant>& set)
    {
        std::cout << "Set analysis: " << &set << " " << &set.front() << std::endl;
    }
};

class TargetClass
{
    std::vector<Ant> m_set;

public:
    void setSetCopy(std::vector<Ant> theSet)
    {
        m_set = theSet;
    }

    void setSetMove(std::vector<Ant>&& theSet)
    {
        m_set = std::move(theSet);
    }

    const std::vector<Ant>& getSet()
    {
        return m_set;
    }
};


void moveSemantics()
{
    std::cout << std::endl << "Move semantics" << std::endl;

    SetCreator sc;
    TargetClass tc1;
    TargetClass tc2;

    // Create set
    auto mySet = sc.createSet(1e5);  // warning - converting double to int
    sc.analyzeSet(mySet);

    // Set set - Copy
    auto start = std::chrono::high_resolution_clock::now();
    tc1.setSetCopy(mySet);
    auto finish = std::chrono::high_resolution_clock::now();

    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
    std::cout << "Copy: " << microseconds.count() << " micro s\n";

    sc.analyzeSet(tc1.getSet());

    // Set set - Move
    start = std::chrono::high_resolution_clock::now();
    tc2.setSetMove(std::move(mySet));
    finish = std::chrono::high_resolution_clock::now();

    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
    std::cout << "Move: " << microseconds.count() << " micro s\n";

    sc.analyzeSet(tc2.getSet());
}