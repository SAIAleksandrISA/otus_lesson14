#include <functional>
#include "task.hpp"
#include "workers.hpp"
#include <iostream>
#include <thread>
#include <memory> 

#include "isafequeue.hpp"
#include "safequeue.hpp"
#include "safepriorityqueue.hpp"

int main()
{
    std::unique_ptr<ISafeQueue<Task>> taskQueue = std::make_unique<SafePriorityQueue<Task>>();

    const int nProducers = 2;
    const int nConsumers = 4;

    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    for (int i = 0; i < nProducers; ++i)
        producers.emplace_back(producer, std::ref(*taskQueue));

    for (int i = 0; i < nConsumers; ++i)
        consumers.emplace_back(consumer, std::ref(*taskQueue));

    for (auto& t : producers)
        t.join();

    taskQueue->finish();

    for (auto& t : consumers)
        t.join();
    return 0;
}