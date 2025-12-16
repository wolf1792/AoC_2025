#include "common.hpp"

class Day3 : public Solver
{
public:
    Day3()
    {
        m_inputs = load_inputs("input_files/day3.txt"sv);
    }
    uint64_t solve() final
    {
        uint64_t result = 0;
        for(auto const [index, line] : std::views::enumerate(m_inputs))
        {
            std::string max_jolt="";
            size_t pos_max_jolt = 0;
            char max_jolt_char = line[0];
            for (size_t pos = 1; pos < line.size()-1; ++pos)
            {
                if(line[pos] > max_jolt_char)
                {
                    max_jolt_char = line[pos];
                    pos_max_jolt = pos;
                }
            }
            max_jolt += max_jolt_char;
            pos_max_jolt++;
            max_jolt_char = line[pos_max_jolt];
            for (size_t pos = pos_max_jolt+1; pos < line.size(); ++pos)
            {
                if(line[pos] > max_jolt_char)
                {
                    max_jolt_char = line[pos];
                    pos_max_jolt = pos;
                }
            }
            max_jolt += max_jolt_char;
            auto partial_res = std::stoull(max_jolt);
            result += partial_res;
        }
        
        return result;
    }
    uint64_t solve2() final
    {   
        uint64_t result = 0;
        for(auto const [index, line] : std::views::enumerate(m_inputs))
        {
            int remaining_length = 11;
            std::string max_jolt="";
            size_t pos_max_jolt = 0;
            char max_jolt_char = line[pos_max_jolt];
            while (remaining_length >= 0)
            {
                for (size_t pos = pos_max_jolt+1; pos < line.size() - remaining_length; ++pos)
                {
                    if(line[pos] > max_jolt_char)
                    {
                        max_jolt_char = line[pos];
                        pos_max_jolt = pos;
                    }
                }
                max_jolt += max_jolt_char;
                pos_max_jolt++;
                max_jolt_char = line[pos_max_jolt];
                remaining_length--;
            }
            auto partial_res = std::stoull(max_jolt);
            result += partial_res;
        }
        
        return result;
    }
private:
    std::vector<std::string> m_inputs;
};