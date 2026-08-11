#pragma once
#include <string>

struct Task
{
    int id;
    std::string name;
    int time_ms;
    int priority;

    bool operator<(const Task& other) const
    {
        if (priority != other.priority)
            return priority < other.priority;

        return id > other.id;
    }
};