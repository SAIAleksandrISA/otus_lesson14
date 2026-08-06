#pragma once
#include "SafeQueue.hpp"
#include "Task.hpp"

// Объявления функций
void producer(SafeQueue<Task>& q);
void consumer(SafeQueue<Task>& q);