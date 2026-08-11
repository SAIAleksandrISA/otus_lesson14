#pragma once
#include "isafequeue.hpp"
#include "task.hpp"

// Объявления функций
void producer(ISafeQueue<Task>& q);
void consumer(ISafeQueue<Task>& q);