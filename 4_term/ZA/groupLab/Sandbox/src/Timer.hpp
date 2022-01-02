#pragma once

#include <chrono>

template <typename Rep, typename Period>
class Timer {
public:
    explicit Timer(std::chrono::duration<Rep, Period>& time)
        : m_Start(std::chrono::high_resolution_clock::now())
        , m_Time(time) {}
    ~Timer() {
        TimePoint end = std::chrono::high_resolution_clock::now();
        m_Time        = std::chrono::duration_cast<std::chrono::duration<Rep, Period>>(end - m_Start);
    }

private:
    using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;

    TimePoint                           m_Start;
    std::chrono::duration<Rep, Period>& m_Time;

}; // class Timer

template <typename Period>
using Duration = std::chrono::duration<int64_t, Period>;

template <typename Period, typename Func, typename... Args>
void GetTime(Duration<Period>& time, Func func, Args&&... args) {
    Timer timer(time);
    func(std::forward<Args>(args)...);
}

template <typename Period, typename Func, typename... Args>
intmax_t GetTime(Func func, Args&&... args) {
    Duration<Period> time;

    {
        Timer timer(time);
        func(std::forward<Args>(args)...);
    }

    return time.count();
}
