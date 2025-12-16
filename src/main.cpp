#include "common.hpp"
#include "day.hpp"

int main(void)
{   
    for(uint8_t day=1; day<=12; day++)
    {
        Day solver(day);
        auto start1 = std::chrono::steady_clock::now().time_since_epoch().count();
        const auto result1 = solver.solve();
        auto stop1 = std::chrono::steady_clock::now().time_since_epoch().count();
        auto start2 = std::chrono::steady_clock::now().time_since_epoch().count();
        const auto result2 = solver.solve2();
        auto stop2 = std::chrono::steady_clock::now().time_since_epoch().count();
        std::println("Day {} results:", day);
        std::println("\t part 1: {}     - solved in ({} ms)", result1, ((stop1-start1)/(1000*1000)));
        std::println("\t part 2: {}     - solved in ({} ms)", result2, ((stop2-start2)/(1000*1000)));
    }
    return 1;   
}