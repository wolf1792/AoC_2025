#include "common.hpp"
#include "day1.hpp"
#include "day2.hpp"
#include "day3.hpp"
#include "day4.hpp"
#include "day5.hpp"
#include "day6.hpp"
#include "day7.hpp"
#include "day8.hpp"
#include "day9.hpp"
#include "day10.hpp"
#include "day11.hpp"
#include "day12.hpp"

class Day
{
public:
    Day(uint8_t day)
    {
        switch(day)
        {
            case 1:
                solver = std::make_unique<Day1>();
                break;
            case 2:
                solver = std::make_unique<Day2>();
                break;
            case 3:
                solver = std::make_unique<Day3>();
                break;
            case 4:
                solver = std::make_unique<Day4>();
                break;
            case 5:
                solver = std::make_unique<Day5>();
                break;
            case 6:
                solver = std::make_unique<Day6>();
                break;
            case 7:
                solver = std::make_unique<Day7>();
                break;
            case 8:
                solver = std::make_unique<Day8>();
                break;
            case 9:
                solver = std::make_unique<Day9>();
                break;
            case 10:
                solver = std::make_unique<Day10>();
                break;
            case 11:
                solver = std::make_unique<Day11>();
                break;
            case 12:
                solver = std::make_unique<Day12>();
                break;
            default:
                solver = nullptr;
        }
    }
    uint64_t solve()
    {
        if(solver)
            return solver->solve();
        return 0xFFFFFFFFFFFFFFFF;
    }
    uint64_t solve2()
    {
        if(solver)
            return solver->solve2();
        return 0xFFFFFFFFFFFFFFFF;
    }

private:
    std::unique_ptr<Solver> solver;
};