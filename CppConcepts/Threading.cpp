#include "stdafx.h"
#include "Threading.h"

#include <iostream>
#include <thread>
#include <random>
#include <algorithm>
#include <iterator>
#include <functional>
#include <future>

// global variable
std::vector<int> myList;

// mutex to lock global variable
std::mutex myMutex;

class CAccumulatorFunctor
{
public:
    void operator()(const std::vector<int> &v, unsigned int beginIndex, unsigned int endIndex)
    {
        _acm = 0;
        for (unsigned int i = beginIndex; i < endIndex; ++i)
        {
            _acm += v[i];
        }
    }
    unsigned long long _acm;
};

void accumulatorFunction(const std::vector<int> &v, unsigned long long &acm, unsigned int beginIndex, unsigned int endIndex)
{
    acm = 0;
    for (unsigned int i = beginIndex; i < endIndex; ++i)
    {
        acm += v[i];
    }
}

std::vector<int> getRandomVector(int size)
{
    // First create an instance of an engine.
    std::random_device rndDevice;
    // Specify the engine and distribution.
    // Generates random integers
    std::mt19937 mersenneEngine{ rndDevice() };
    std::uniform_int_distribution<int> dist{ 1, 52 };

    auto gen = [&dist, &mersenneEngine]()
    {
        return dist(mersenneEngine);
    };

    std::vector<int> vec(size);
    std::generate(begin(vec), end(vec), gen);

    return vec;
}

void threadingExample1(std::vector<int>& v)
{
    std::cout << std::endl << "Pointer to function" << std::endl;
    //Pointer to function
    unsigned long long acm1 = 0;
    unsigned long long acm2 = 0;
    std::thread t1(accumulatorFunction, std::ref(v), std::ref(acm1), 0, v.size() / 2);
    std::thread t2(accumulatorFunction, std::ref(v), std::ref(acm2), v.size() / 2, v.size());
    t1.join();
    t2.join();

    std::cout << "acm1: " << acm1 << std::endl;
    std::cout << "acm2: " << acm2 << std::endl;
    std::cout << "acm1 + acm2: " << acm1 + acm2 << std::endl;
}

void threadingExample2(std::vector<int>& v)
{
    std::cout << std::endl << "Creating Thread using Functor" << std::endl;
    //Creating Thread using Functor
    CAccumulatorFunctor accumulator1 = CAccumulatorFunctor();
    CAccumulatorFunctor accumulator2 = CAccumulatorFunctor();
    std::thread t1(std::ref(accumulator1), std::ref(v), 0, v.size() / 2);
    std::thread t2(std::ref(accumulator2), std::ref(v), v.size() / 2, v.size());
    t1.join();
    t2.join();

    std::cout << "acm1: " << accumulator1._acm << std::endl;
    std::cout << "acm2: " << accumulator2._acm << std::endl;
    std::cout << "accumulator1._acm + accumulator2._acm : " << accumulator1._acm + accumulator2._acm << std::endl;
}

void threadingExample3(std::vector<int>& v)
{
    std::cout << std::endl << "Tasks, Future, and Promises" << std::endl;
    // Tasks, Future, and Promises
    auto f1 = [](std::vector<int> &v, unsigned int left, unsigned int right)
    {
        unsigned long long acm = 0;
        for (unsigned int i = left; i < right; ++i)
        {
            acm += v[i];
        }

        return acm;
    };

    auto t1 = std::async(f1, std::ref(v), 0, v.size() / 2);
    auto t2 = std::async(f1, std::ref(v), v.size() / 2, v.size());

    // other stuff can be done here
    unsigned long long acm1 = t1.get();
    unsigned long long acm2 = t2.get();

    std::cout << "acm1: " << acm1 << std::endl;
    std::cout << "acm2: " << acm2 << std::endl;
    std::cout << "acm1 + acm2: " << acm1 + acm2 << std::endl;
}

void threadFunction()
{
    //for (size_t i = 0; i < 15; i++)
    {
        //Using std::lock_guard (recommended)
        std::lock_guard<std::mutex> guard(myMutex);
        std::thread::id this_id = std::this_thread::get_id();
        std::cout << "From thread " << this_id << std::endl;
        //std::cout << "Iteration " << i << " from thread " << this_id << std::endl;
        //std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void threadingExample4()
{
    std::cout << std::endl << "Using std::lock_guard (recommended)" << std::endl;
    std::thread t1(threadFunction);
    std::thread t2(threadFunction);
    std::thread t3(threadFunction);

    t1.join();
    t2.join();
    t3.join();
}

void threadingExample5()
{
    std::cout << std::endl << "hardware_cuncurrency" << std::endl;

    unsigned int c = std::thread::hardware_concurrency();
    std::cout << "number of cores: " << c << std::endl;
}

void addToList(int max, int interval)
{
    // the access to this function is mutually exclusive
    std::lock_guard<std::mutex> guard(myMutex);
    for (int i = 0; i < max; i++)
    {
        if ((i % interval) == 0)
        {
            myList.push_back(i);
            std::thread::id this_id = std::this_thread::get_id();
            std::cout << "adding" << i << "(thread " << this_id << ")" << std::endl;
        }
    }
}

void printList()
{
    // the access to this function is mutually exclusive
    std::lock_guard<std::mutex> guard(myMutex);
    for (auto itr = myList.begin(), end_itr = myList.end(); itr != end_itr; ++itr)
    {
        //std::cout << *itr << ",";
        std::cout << "print" << *itr << std::endl;
    }
}

void threadingExample6()
{
    std::cout << std::endl << "Threads synchronization" << std::endl;
    int max = 100;

    std::thread t1(addToList, max, 1);
    std::thread t2(addToList, max, 10);
    std::thread t3(printList);

    t1.join();
    t2.join();
    t3.join();
}

void threading()
{
    std::cout << std::endl << "Threading" << std::endl;
    std::cout << "Hello Parallel World!\n";

    std::vector<int> v = getRandomVector(1000);

    threadingExample1(v);
    threadingExample2(v);
    threadingExample3(v);
    threadingExample4();
    threadingExample5();
    threadingExample6();

    std::cout << std::endl << std::endl << "Goodbye" << std::endl;
}