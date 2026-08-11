#include <iostream>
#include <cassert>
#include "safepriorityqueue.hpp"
#include "Task.hpp"

void test_priority_logic() 
{
    SafePriorityQueue<Task> q;

    q.push({ 1, "Low", 0, 1 });
    q.push({ 2, "High", 0, 10 });

    Task t1, t2;
    q.pop(t1);
    q.pop(t2);

    assert(t1.priority == 10);
    assert(t2.priority == 1);

    std::cout << "Priority test passed!" << std::endl;
}

int main() 
{
    test_priority_logic();
    return 0;
}