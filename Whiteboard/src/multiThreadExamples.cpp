#include <iostream>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>

std::deque<int> taskQueue;
std::mutex queueMutex;
std::condition_variable cv;

void producer() {
    for (int i = 1; i <= 5; ++i) {
        std::unique_lock<std::mutex> lock(queueMutex);
        taskQueue.push_back(i);  // Add task to the back
        std::cout << "Produced: " << i << "\n";
        lock.unlock();
        cv.notify_one();  // Notify a waiting thread
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);
        cv.wait(lock, [] { return !taskQueue.empty(); });  // Wait until queue is not empty

        int task = taskQueue.front();
        taskQueue.pop_front();
        std::cout << "Consumed: " << task << "\n";
        lock.unlock();

        if (task == 5) break;  // Stop condition
    }
}

int wmain() {
    std::thread t1(producer);
    std::thread t2(consumer);

    t1.join();
    t2.join();

    return 0;
}