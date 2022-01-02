#pragma once

#include <iostream>
#include <chrono>

class LogDuration {
public:
    explicit LogDuration(std::string caption)
        : m_Start(std::chrono::steady_clock::now())
        , m_Caption(std::move(caption)) {}
    ~LogDuration() {
        auto end = std::chrono::steady_clock::now();

        std::cout << m_Caption << ": ";
        std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - m_Start).count() << " ms" << std::endl;
        std::cout << std::endl;
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> m_Start;
    std::string                                        m_Caption;

}; // class LogDuration

#define LOG_DURATION(caption) LogDuration __FILE__##__LINE__##_LogDuration(caption)