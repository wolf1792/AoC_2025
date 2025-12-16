#include "common.hpp"

class Day10 : public Solver
{
using Lights = std::bitset<10>;
using Buttons = std::vector<std::bitset<10>>;
using Joltage = std::vector<size_t>;
public:
    Day10()
    {
        m_inputs = load_inputs("input_files/day10.txt"sv);
    }

    uint64_t solve() final
    {
        uint64_t res = 0;
        for (auto const& line : m_inputs)
        {
            res += solve_line(line);
        }
        return res;
    }

    uint64_t solve2() final
    {
        std::println("Day 10: \n\tGave up solving part 2, tried to adapt code from part 1, but was impossible. It required linear algebra.\n\
        Just ended up taking a python script that used an external library to do that (ilp_solver_day10.py).\n\
        No fun in this.");
        return 0;
    }

private:
    Lights get_lights(std::string& line)
    {
        constexpr char LIGHT_OFF = '.';
        constexpr char LIGHT_ON = '#';
        Lights lights;
        uint32_t pos = 0;
        while(line.at(0) != '(')
        {
            if(line.at(0) == LIGHT_ON)
            {
                lights[pos] = true;
                pos++;
            }
            else if(line.at(0) == LIGHT_OFF)
            {
                pos++;
            }
            line.erase(0,1);
        }
        return lights;
    }
    Buttons get_buttons(std::string& line)
    {
        Buttons buttons;
        bool wire_open = false;
        while(line.at(0) != '{')
        {
            if(line.at(0) == '(')
            {
                wire_open = true;
                buttons.emplace_back();
            }
            else if(line.at(0) == ')')
            {
                wire_open = false;
            }
            else if(wire_open)
            {
                if(isdigit(line.at(0)))
                {
                    short wire = line.at(0) - '0';
                    buttons.back()[wire]=true;
                }
                else if(line.at(0) == ',')
                {
                    // ignore
                }
                else
                {
                    std::println("Unexpected character in wiring: {}", line);
                }
            }
            line.erase(0, 1);
        }
        return buttons;
    }
    Joltage get_joltage(std::string& line)
    {
        Joltage jol;
        line.erase(0, 1); // remove '{'
        line.erase(line.size()-1, 1); // remove '}'
        auto joltages = tokenize(line, ',');
        for(auto j : joltages)
        {
            jol.push_back(std::stoul(j));
        }
        return jol;
    }

    static void press_button(Lights& lights, Lights const& pressed)
    {
        lights ^= pressed;
    }
    static bool try_sequence(Buttons const& buttons, Lights const& target)
    {
        Lights attempt;
        for(auto button : buttons)
        {
            press_button(attempt, button);
        }
        return (attempt == target);
    }

    std::vector<Buttons> build_combinations(Buttons const& buttons, size_t length)
    {
        if (length == 0) {return {};}

        std::vector<Buttons> result;
        std::vector<Lights> current_combination;
        auto generate_combinations_rec = [&](auto self, int start_index){            
            if (current_combination.size() == length) {
                result.push_back(current_combination);
                return;
            }
            for (size_t i = start_index; i < buttons.size(); ++i) {
                current_combination.push_back(buttons[i]);
                self(self, i + 1);
                current_combination.pop_back();
            }
        };
    
        generate_combinations_rec(generate_combinations_rec, 0);
        return result;
    }

    uint64_t solve_line(std::string line)
    {
        Lights const target = get_lights(line);
        Buttons const buttons = get_buttons(line);
        size_t press_limit = 0;
        
        while(true)
        {
            press_limit++;
            for(auto const& seq : build_combinations(buttons, press_limit))
            {
                bool found = try_sequence(seq, target);
                if(found)
                {
                    return seq.size();
                }
            }
        }
        return 0;
    }
    
    std::vector<std::string> m_inputs;
};