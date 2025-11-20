#pragma once
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic>

class ThreadPool {
public:
    explicit ThreadPool(size_t numThreads = std::thread::hardware_concurrency())
        : stopFlag(false)
    {
        for (size_t i = 0; i < numThreads; ++i)
        {
            workers.emplace_back([this] {
                while (true)
                {
                    std::function<void()> task;

                    // Critical section for accessing the queue
                    {
                        std::unique_lock<std::mutex> lock(this->queueMutex);

                        this->condition.wait(lock, [this] {
                            return this->stopFlag || !this->tasks.empty();
                        });

                        if (this->stopFlag && this->tasks.empty())
                            return;

                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }

                    task(); // execute the job
                }
            });
        }
    }

    // Submit a task to the pool
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args)
        -> std::future<typename std::invoke_result<F, Args...>::type>
    {
        using return_type = typename std::invoke_result<F, Args...>::type;

        auto packagedTask = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> result = packagedTask->get_future();

        {
            std::unique_lock<std::mutex> lock(queueMutex);

            // Do not allow enqueue after stopping
            if (stopFlag)
                throw std::runtime_error("ThreadPool is stopped");

            tasks.emplace([packagedTask]() { (*packagedTask)(); });
        }

        condition.notify_one();
        return result;
    }

    // Graceful shutdown
    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stopFlag = true;
        }

        condition.notify_all();

        for (std::thread &worker : workers)
            worker.join();
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;

    std::atomic<bool> stopFlag;
};
