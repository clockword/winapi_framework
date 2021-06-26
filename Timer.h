#pragma once

#include <atomic>

class Timer {
    std::atomic<bool> active{ true };

public:
    template<typename Function>
    void setTimeout(Function function, int delay);
    template<typename Function>
    void setInterval(Function function, int interval);
    void stop();

};