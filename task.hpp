#pragma once // Защита от повторного включения файла
#include <string>

struct Task
{
    int id;
    std::string name;
    int time_ms;
};