#include "workers.hpp"
#include <iostream>
#include <thread>
#include <string>
#include <chrono>

void producer(ISafeQueue<Task>& q)
{
    for (int i = 1; i <= 5; ++i)
    {
        Task t = { i, "Task_" + std::to_string(i), 500, i%3 };
        std::cout << "[Producer] Create: " << t.name << std::endl;
        q.push(t);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
    q.finish();
    std::cout << "[Producer] Finish." << std::endl;
}

void consumer(ISafeQueue<Task>& q)
{
    Task t;
    while (q.pop(t))
    {
        std::cout << "[Consumer] Wait: " << t.name << "..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(t.time_ms));
        std::cout << "[Consumer] Done: " << t.name << std::endl;
    }

    std::cout << "[Consumer] Empty, exit." << std::endl;
}