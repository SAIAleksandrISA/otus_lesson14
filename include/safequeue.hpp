#pragma once
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "isafequeue.hpp"

template <typename T>
class SafeQueue : public ISafeQueue<T>
{
public:
    ~SafeQueue() override
    {
        finish();
    }

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
        m_cond.wait(lock, [this] { return !m_queue.empty() || m_finished.load(); });

        if (m_queue.empty() && m_finished)
            return false;

        value = std::move(m_queue.front());
        m_queue.pop();
        return true;
    }

    void finish() override
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_finished.store(true);
        m_cond.notify_all();
    }

    bool empty() const override 
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

    bool is_finished() const override 
    {
        return m_finished.load();
    }

private:
    std::queue<T> m_queue;
    mutable std::mutex m_mutex;
    std::condition_variable m_cond;
    std::atomic<bool> m_finished{ false };
};
