#pragma once
#include <atomic>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <algorithm>
#include "isafequeue.hpp"

template <typename T>
class SafePriorityQueue : public ISafeQueue<T>
{
public:
    ~SafePriorityQueue() override
    {
        finish();
    }

public:
    void push(T value)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_container.push_back(std::move(value));
        std::push_heap(m_container.begin(), m_container.end());
        m_cond.notify_one();
    }

    bool pop(T& value) 
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_cond.wait(lock, [this] { return !m_container.empty() || m_finished.load(); });

        if (m_container.empty() && m_finished.load()) 
            return false;

        std::pop_heap(m_container.begin(), m_container.end());
        value = std::move(m_container.back());
        m_container.pop_back();

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
        return m_container.empty();
    }

    bool is_finished() const override 
    {
        return m_finished.load();
    }

private:
    std::vector<T> m_container;
    mutable  std::mutex m_mutex;
    std::condition_variable m_cond;
    std::atomic<bool> m_finished{ false };
};