#pragma once
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <utility>

template <typename T>
class SafeQueue
{
public:
    void push(T value)
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_queue.push(std::move(value));
        }
        m_cond.notify_one();
    }

    bool pop(T& value)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait(lock, [this] { return !m_queue.empty() || m_finished; });

        if (m_queue.empty() && m_finished)
        {
            return false;
        }

        value = std::move(m_queue.front());
        m_queue.pop();
        return true;
    }

    void finish()
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_finished = true;
        }
        m_cond.notify_all();
    }

private:
    std::queue<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_cond;
    bool m_finished = false;
};