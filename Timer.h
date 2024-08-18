#pragma once
#include <chrono>
#include <string>
#include <iostream>

namespace Unit {
    typedef std::chrono::microseconds microseconds;
    typedef std::chrono::milliseconds milliseconds;
    typedef std::chrono::seconds seconds;
    typedef std::chrono::minutes minutes;
}

template<typename T>
class Timer {
public:
    Timer(std::string ID = "Timer") {
        start = std::chrono::high_resolution_clock::now();
        this->ID = ID;
    }

    ~Timer() {
        end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<T>(end - start);
        std::cout << ID << ": " << duration.count() << std::endl;
    }
private:
    std::chrono::high_resolution_clock::time_point start, end;
    std::string ID;
};