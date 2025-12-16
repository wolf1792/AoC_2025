#include "common.hpp"

class Day7 : public Solver
{
public:
    Day7()
    {
        m_inputs = load_inputs("input_files/day7.txt"sv);
    }
    uint64_t solve() final
    {
        uint64_t result = 0;
        std::set<uint64_t> tachyion_rays;
        for(auto const& row : m_inputs)
        {    
            for(auto const [index, c]  : std::views::enumerate(row))
            {
                if(c == 'S')
                {
                    tachyion_rays.insert(index);
                }
                else if(c == '^')
                {
                    if(tachyion_rays.contains(index))
                    {
                        result ++;
                        tachyion_rays.erase(index);
                        tachyion_rays.insert(index-1);
                        tachyion_rays.insert(index+1);
                    }
                }
            }
        }

        return result;
    }
    uint64_t solve2() final
    {
        uint64_t result = 0;
        std::map<uint64_t, uint64_t> tachyion_rays;
        for(auto const& row : m_inputs)
        {    
            for(auto const [index, c]  : std::views::enumerate(row))
            {
                if(c == 'S')
                {
                    tachyion_rays[index]= 1;
                }
                else if(c == '^')
                {
                    if(tachyion_rays.contains(index))
                    {
                        tachyion_rays[index-1] += tachyion_rays[index]; 
                        tachyion_rays[index+1] += tachyion_rays[index];

                        tachyion_rays.erase(index);
                    }
                }
            }
        }

        for(auto const& [key, val] : tachyion_rays)
        {
            result += val;
        }
        return result;
    }

private:
    std::vector<std::string> m_inputs;
};


