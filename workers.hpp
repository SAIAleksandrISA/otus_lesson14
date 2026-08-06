#pragma once
#include "safequeue.hpp"
#include "task.hpp"

// Объявления функций
void producer(SafeQueue<Task>& q);
void consumer(SafeQueue<Task>& q);