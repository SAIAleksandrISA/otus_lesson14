#include <iostream>
#include <thread>
#include <vector>
#include <atomic>
#include <cassert>
#include "safequeue.hpp"
#include "task.hpp"

void stress_test() 
{
    SafeQueue<Task> q;
    std::atomic<int> processed_count{ 0 };
    const int N = 1000;

    std::thread producer([&]() 
        {
        for (int i = 0; i < N; ++i) q.push({ i, "Task", 0, 0 });
        q.finish();
        });

    std::thread consumer([&]() 
        {
        Task t;
        while (q.pop(t)) 
            processed_count++;
        });

    producer.join();
    consumer.join();

    assert(processed_count == N);
    std::cout << "Stress test passed! Processed " << processed_count << " tasks." << std::endl;
}

int main() 
{
    stress_test();
    return 0;
}