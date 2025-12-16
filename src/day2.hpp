#include "common.hpp"

class Day2 : public Solver
{
public:
    Day2()
    {
        auto const inputs = load_inputs("input_files/day2.txt"sv);
        m_inputs = parse_input(inputs);
    }

    std::vector<std::pair<uint64_t, uint64_t>> parse_input(auto const& input)
    {
        std::vector<std::pair<uint64_t, uint64_t>> parsed; 
        for (auto const& line : input)
        {
            auto ranges = tokenize(line, ',');
            for(const auto& range : ranges)
            {
                auto dash_pos = range.find('-');
                uint64_t first =std::stoull(range.substr(0, dash_pos));  
                uint64_t second =std::stoull(range.substr(dash_pos+1));  
                parsed.emplace_back(first, second);
            }
        }
        return parsed;
    }

    bool has_repeated_digits(uint64_t number)
    {
        std::string num_str = std::to_string(number);
        if(num_str.size()%2 != 0)
        {
            return false;
        }
        //std::string const half = num_str.substr(0, num_str.size()/2);
        //return (half == num_str.substr(num_str.size()/2));
        std::string_view fhalf(num_str.c_str(), num_str.size()/2);
        std::string_view shalf(num_str.c_str()+(num_str.size()/2), num_str.size()/2);
        return (fhalf == shalf);
    }

    uint64_t solve() final
    {
        uint64_t result = 0;
        for(auto [first, second] : m_inputs){
            while(first<=second)
            {
                if(has_repeated_digits(first))
                {
                    result+=first;
                }
                first++;
            }
        }
        return result;
    }

    bool has_multiple_repeated_digits(uint64_t number)
    {
        const std::string num_str = std::to_string(number);
        for(size_t c=1;c<num_str.length();c++)
        {
            if(c > num_str.length()/2){
                return false;//impossible to repeat twice this length
            }
            if(num_str.length()%c != 0){
                continue;//not multiple, cannot repeat
            }

            std::string_view sequence(num_str.c_str(), c);
            size_t checked = 0;
            bool equal=true;
            while(checked<num_str.length() && equal)
            {
                std::string_view to_check(num_str.c_str()+checked, c);
                if(to_check!=sequence)
                {
                    equal=false;
                }
                checked+=c;
            }
            if(equal)
            {
                return true;
            }
        }
        return false;
    }

    uint64_t solve2() final
    {   
        uint64_t result = 0;
        for(auto [first, second] : m_inputs){
            while(first<=second)
            {
                if(has_multiple_repeated_digits(first))
                {
                    result+=first;
                }
                first++;
            }
        }
        return result;
    }
private:
    std::vector<std::pair<uint64_t, uint64_t>> m_inputs;
};