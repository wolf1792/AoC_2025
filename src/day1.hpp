#include "common.hpp"

class Day1 : public Solver
{
public:
    Day1()
    {
        m_inputs = load_inputs("input_files/day1.txt"sv);
    }
    uint64_t solve() final
    {
        int current_dial =50;
        uint64_t result = 0;
        for(const auto& input : m_inputs){
            char direction = input[0];
            int amount = std::stoi(input.substr(1)) % 100;    
            if(direction == 'L'){
                amount = -amount;
            }            
            current_dial += amount;
            if(current_dial>=100)
                current_dial = current_dial%100;
            else if(current_dial<0)
                current_dial = 100-(std::abs(current_dial));
            
            if(current_dial==0)
                result++;
        }
        return result;
    }


    uint64_t solve2() final
    {
        int current_dial =50;
        uint64_t result = 0;
        for(const auto& input : m_inputs){
            char direction = input[0];
            int amount = std::stoi(input.substr(1));    
            int multiple_rounds = amount/100;
            amount = amount % 100;
            if(direction == 'L'){
                amount = -amount;
            }         
            const auto prev_dial = current_dial;   
            current_dial += amount;
            if(current_dial>=100)
            {
                current_dial = current_dial%100;
                result++; 
            }
            else if(current_dial<0)
            {
                current_dial = 100-(std::abs(current_dial));
                if(prev_dial != 0)
                {
                    result++; 
                }
            }
            else if(current_dial==0)
            {
                result++; 
            }
        
            result+=multiple_rounds;            
        }
        return result;
    }
private:
    std::vector<std::string> m_inputs;
};