#include <iostream>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>

std::deque<int> taskQueue;
std::mutex queueMutex;
std::condition_variable cv;

bool producerDone = false;

void producer() {
    for (int i = 1; i <= 50000; ++i) {
        std::unique_lock<std::mutex> lock(queueMutex);
        taskQueue.push_back(i);  // Add task to the back
        std::cout << "Produced: " << i << "\n";
        lock.unlock();
        cv.notify_one();  // Notify a waiting thread
        // std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    producerDone = true;
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);
        cv.wait(lock, [] { return !taskQueue.empty(); });  // Wait until queue is not empty

        int task = taskQueue.front();
        taskQueue.pop_front();
        std::cout << "Consumed: " << task << " !!!!!!!!!!\n";
        lock.unlock();

        if (producerDone && taskQueue.empty()) break;  // Stop condition
    }
}

int wmain() {
    std::thread t1(producer);
    std::thread t2(consumer);
    std::thread t3(consumer);

    t1.join();
    t2.join();
    t3.join();


    std::cout << "all done \n";
    return 0;
}