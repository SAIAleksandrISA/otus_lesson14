#pragma once

template <typename T>
class ISafeQueue
{
public:
    virtual ~ISafeQueue() = default;

    virtual void push(T value) = 0;
    virtual bool pop(T& value) = 0;
    virtual void finish() = 0;
};



