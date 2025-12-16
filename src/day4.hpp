#include "common.hpp"

class Day4 : public Solver
{
public:
    Day4()
    {
        auto const inputs = load_inputs("input_files/day4.txt"sv);
        m_map = parse_input(inputs);
    }
    
    std::vector<std::vector<bool>> parse_input(auto const& input)
    {
        std::vector<std::vector<bool>> map;
        for (const auto& line : input)
        {
            std::vector<bool> row;
            for (const char c : line)
            {
                row.push_back(c == '@');
            }
            map.push_back(row);
        }
        return map;
    }

    bool is_cell_accessibile(size_t x, size_t y)
    {
        if (x >= m_map.size() || y >= m_map[x].size()) {
            return false; //out of bound
        }
        if (!m_map[x][y]) {
            return false;
        }

        int around[] = {1, 0, -1};
        size_t around_free = 0;
        for(auto ax : around)
        {
            for(auto ay : around)
            {
                if (ax == 0 && ay == 0) continue; // skip the cell itself
                size_t new_x = x + ax;
                size_t new_y = y + ay;
                if (new_x >= m_map.size() || new_y >= m_map[x].size())
                {
                    around_free++;
                }
                else if(!m_map[new_x][new_y]) 
                {
                    around_free++;
                }
            }
        }

        return (around_free>4);
    }

    uint64_t solve() final
    {
        uint64_t result = 0;
        for(size_t x=0; x < m_map.size(); ++x)
        {
            for(size_t y=0; y < m_map[x].size(); ++y)
            {
                if (is_cell_accessibile(x, y)) {
                    result++;
                }
            }
        }
        
        return result;
    }
    
    uint64_t solve2() final
    {   
        uint64_t result = 0;
        uint64_t prev_result = 0;
        do
        {
            prev_result = result;
            for(size_t x=0; x < m_map.size(); ++x)
            {
                for(size_t y=0; y < m_map[x].size(); ++y)
                {
                    if (is_cell_accessibile(x, y)) {
                        result++;
                        m_map[x][y] = false; // Mark the cell as processed
                    }
                }
            }
        }
        while(result != prev_result);//loop while some work can be done
        
        return result;
    }
private:
    std::vector<std::vector<bool>> m_map;
};