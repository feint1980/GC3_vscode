#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <functional>

class ThreadPool {
public:
    ThreadPool(size_t num_threads);
    ~ThreadPool();
    
    void enqueue(std::function<void()> task);

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;

    void workerThread();
};

// Constructor: Create worker threads
ThreadPool::ThreadPool(size_t num_threads) : stop(false) {
    for (size_t i = 0; i < num_threads; ++i) {
        workers.emplace_back(&ThreadPool::workerThread, this);
    }
}

// Add a task to the queue
void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        tasks.push(task);
    }
    condition.notify_one();  // Wake up one worker thread
}

// Worker thread function
void ThreadPool::workerThread() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            condition.wait(lock, [this] { return stop || !tasks.empty(); });

            if (stop && tasks.empty()) return;  // Exit thread

            task = std::move(tasks.front());
            tasks.pop();
        }
        task();  // Execute task
    }
}

// Destructor: Join all threads
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop = true;
    }
    condition.notify_all();
    for (std::thread &worker : workers) {
        worker.join();
    }
}

// Example Task Function
void exampleTask(int id) {
    std::cout << "Task " << id << " is running on thread " << std::this_thread::get_id() << "\n";
}

// Main function
int wmain() {
    const size_t num_threads = std::thread::hardware_concurrency();  // Optimal thread count
    ThreadPool pool(num_threads);

    // Enqueue 10,000 tasks
    for (int i = 0; i < 10000; ++i) {
        pool.enqueue([i] { exampleTask(i); });
    }

    return 0;
}
