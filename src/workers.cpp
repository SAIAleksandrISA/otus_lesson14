#include "workers.hpp"
#include <iostream>
#include <thread>
#include <string>
#include <chrono>

void producer(ISafeQueue<Task>& q, int producerId)
{
    for (int i = 1; i <= 5; ++i)
    {
        int uniqueId = producerId * 10 + i;
        int priority = i % 3;
        Task t = { uniqueId, "Task_" + std::to_string(uniqueId), 500, priority };

        std::cout << "[Producer " << producerId << "] Create: " << t.name
            << " Priority: " << t.priority << std::endl;

        q.push(t);
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
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