#include <iostream>
#include <chrono>
#include "safequeue.hpp"
#include "task.hpp"

int main() 
{
    SafeQueue<Task> q;
    const int N = 50000;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < N; ++i) q.push({ i, "T", 0, 0 });
    q.finish();

    Task t;
    while (q.pop(t));

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;

    std::cout << "Processed " << N << " tasks in " << diff.count() << " seconds." << std::endl;
    return 0;
}