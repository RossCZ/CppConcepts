#include "stdafx.h"
#include "ThreadPool.h"

#include <iostream>
#include <condition_variable>
#include <functional>
#include <future>
#include <vector>
#include <thread>
#include <queue>

class ThreadPool
{
public:
    using Task = std::function<void()>;

    explicit ThreadPool(std::size_t numThreads)
    {
        start(numThreads);
    }

    ~ThreadPool()
    {
        stop();
    }

    template<class T>
    auto enqueue(T task)->std::future<decltype(task())>
    {
        auto wrapper = std::make_shared<std::packaged_task<decltype(task()) ()>>(std::move(task));

        // scope of a lock for mutex
        {
            std::unique_lock<std::mutex> lock(mEventMutex);
            mTasks.emplace([=] {
                (*wrapper)();
            });
        }

        mEventVar.notify_one();
        return wrapper->get_future();
    }

private:
    std::vector<std::thread> mThreads;

    std::condition_variable mEventVar;

    std::mutex mEventMutex;
    bool mStopping = false;

    std::queue<Task> mTasks;

    void start(std::size_t numThreads)
    {
        for (auto i = 0u; i < numThreads; i++)
        {
            mThreads.emplace_back([=] {
                while (true)
                {
                    Task task;

                    // lock only for necessary time
                    {
                        std::unique_lock<std::mutex> lock(mEventMutex);

                        mEventVar.wait(lock, [=] { return mStopping || !mTasks.empty();  });

                        if (mStopping && mTasks.empty())
                            break;

                        task = std::move(mTasks.front());
                        mTasks.pop();
                    }

                    task();
                }
            });
        }
    }

    void stop() noexcept
    {
        {
            std::unique_lock<std::mutex> lock(mEventMutex);
            mStopping = true;
        }

        mEventVar.notify_all();

        for (auto& thread : mThreads)
            thread.join();
    }
};

class MyObject
{
    int id;
public:
    MyObject(int id)
    {
        this->id = id;
    }

    int getRepresentation()
    {
        int result = id % 10 + 1;

        int sleepTime = (result == 10) ? 5000 : 150;
        std::chrono::milliseconds timespan(sleepTime);
        std::this_thread::sleep_for(timespan);

        return result;
    }
};

void threadPool()
{
    std::cout << std::endl << "Thread pool" << std::endl;

    std::vector<MyObject> myObjects;
    for (int i = 0; i < 100; i++)
    {
        myObjects.push_back(MyObject(i));
    }

    auto generatorFunction = [](MyObject& myObject)
    {
        std::cout << "\t" << myObject.getRepresentation() << std::endl;
    };

    auto start = std::chrono::high_resolution_clock::now();

    {
        ThreadPool pool(32);
        for (MyObject& myObject : myObjects)
        {
            //generatorFunction(myObject);

            pool.enqueue([=, &myObject] {
                generatorFunction(myObject);
            });
        }
    }

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    // basic example
    //{
    //    ThreadPool pool(36);

    //    auto f1 = pool.enqueue([] {
    //        return 1;
    //    });

    //    auto f2 = pool.enqueue([] {
    //        return 2;
    //    });

    //    auto f3 = pool.enqueue([] {
    //        std::cout << "hello" << std::endl;
    //    });

    //    std::cout << (f1.get() + f2.get()) << std::endl;
    //}
}