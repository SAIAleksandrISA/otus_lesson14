#include "SafeQueue.hpp"
#include "Task.hpp"
#include "Workers.hpp"
#include <iostream>
#include <thread>

int main()
{
    SafeQueue<Task> taskQueue;

    std::thread t1(producer, std::ref(taskQueue));
    std::thread t2(consumer, std::ref(taskQueue));

    t1.join();
    t2.join();

    std::cout << "Programm finish." << std::endl;
    return 0;
}