#include <iostream>
#include <vector>
#include "safepriorityqueue.hpp"
#include "task.hpp"

int main()
{
    SafePriorityQueue<Task> q;

    q.push({ 1, "Low", 500, 1 });
    q.push({ 2, "High", 500, 10 });
    q.push({ 3, "Medium", 500, 5 });

    q.finish();

    Task t;
    std::vector<int> results;
    while (q.pop(t)) {
        results.push_back(t.priority);
        std::cout << "Popped: " << t.name << " with priority: " << t.priority << std::endl;
    }

    if (results[0] == 10 && results[1] == 5 && results[2] == 1)
        std::cout << "Priority test passed!" << std::endl;
    else
    {
        std::cerr << "Priority test failed!" << std::endl;
        return 1;
    }

    return 0;
}