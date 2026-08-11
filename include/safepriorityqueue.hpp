#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "isafequeue.hpp"

template <typename T>
class SafePriorityQueue : public ISafeQueue<T>
{
public:
    void push(T value) override
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.push(std::move(value));
        }
        m_cond.notify_one();
    }

    bool pop(T& value) override
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait(lock, [this] { return !m_queue.empty() || m_finished; });

        if (m_queue.empty() && m_finished)
        {
            return false;
        }

        // Используем const_cast для извлечения элемента из priority_queue
        value = std::move(const_cast<T&>(m_queue.top()));
        m_queue.pop();
        return true;
    }

    void finish() override
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_finished = true;
        }
        m_cond.notify_all();
    }

private:
    std::priority_queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cond;
    bool m_finished = false;
};