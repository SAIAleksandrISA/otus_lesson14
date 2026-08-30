#pragma once
#include "isafequeue.hpp"
#include "task.hpp"

// Объявления функций
void producer(ISafeQueue<Task>& q, int producerId);
void consumer(ISafeQueue<Task>& q);