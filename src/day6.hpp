#include "common.hpp"

class Day6 : public Solver
{
public:
    Day6()
    {
        m_inputs1 = parse_inputs(load_inputs("input_files/day6.txt"sv));
        m_inputs2 = load_inputs("input_files/day6.txt"sv);
    }

    std::vector<std::vector<std::string>> parse_inputs(auto const& lines)
    {
        std::vector<std::vector<std::string>> inputs;
        for(auto const& str:lines)
        {
            auto line = tokenize(str, ' ');
            //remove empty strings, not needed now and caused by multiple spaces in input.
            auto new_end = std::remove_if(line.begin(), line.end(), [](const std::string& s) {return s.empty();});
            line.erase(new_end, line.end());
            inputs.push_back(line);
        }
        return inputs;
    }

    uint64_t solve() final
    {
        uint64_t result = 0;
        for(size_t index = 0; index < m_inputs1[0].size(); index++)
        {
            uint64_t partial_res = 0;
            
            char sign = m_inputs1[m_inputs1.size()-1][index].at(0);
            
            for(size_t col = 0; col < m_inputs1.size()-1; col++)
            {
                auto const operand = std::stoull(m_inputs1[col][index]);
                if(sign == '+')
                {
                    partial_res+= operand;
                }
                else if(sign == '*')
                {
                    partial_res = partial_res == 0 ? operand : partial_res * operand;
                }
            }
            result += partial_res;
        }

        return result;
    }

    uint64_t solve2() final
    {
        uint64_t result = 0;
        uint64_t partial_res = 0;
        char sign = ' ';
        for(size_t index = 0; index < m_inputs2[0].size(); index++)
        {    
            bool all_spaces = true;
            std::string current_num = "";
            for(size_t col = 0; col < m_inputs2.size(); col++)
            {
                if(m_inputs2[col][index] != ' '){
                    if(col == m_inputs2.size()-1)
                    {
                        sign = m_inputs2[col][index];
                    }
                    else
                    {
                        current_num += m_inputs2[col][index];
                    }
                    all_spaces = false;
                }
            }
            if (all_spaces)
            {
                result += partial_res;  
                partial_res = 0;    
                sign = ' ';      
                continue;
            }
            
            auto const operand = std::stoull(current_num);
            if(sign == '+')
            {
                partial_res+= operand;
            }
            else if(sign == '*')
            {
                partial_res = partial_res == 0 ? operand : partial_res * operand;
            }
        }
        result += partial_res;

        return result;
    }

private:
    std::vector<std::vector<std::string>> m_inputs1;
    std::vector<std::string> m_inputs2;
};