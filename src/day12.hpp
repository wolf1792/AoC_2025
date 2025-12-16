#include "common.hpp"

class FillerTest
{
    public:
    FillerTest(uint64_t base, uint64_t heigth) 
    : m_area(base*heigth), 
    m_available_area(m_area){
        m_2d.resize(base);
        for(auto& row: m_2d)
        {
            row.resize(heigth);
        }
    };

    bool add_shape()
    {
        if(m_available_area < 9)
        {
            return false;
        }

        for(size_t i = 0; i< m_2d.size()-2; i++)
        {
            for(size_t j = 0; j< m_2d[i].size()-2; j++)
            {
                bool square_free = true;
                const std::vector<uint8_t> neigh{0, 1, 2};
                for(auto n: neigh)
                {
                    for(auto n2: neigh)
                    {
                        if(m_2d[i+n][j+n2])
                        {
                            square_free=false;
                        }
                    }
                }
                if(square_free)
                {
                    for(auto n: neigh)
                    {
                        for(auto n2: neigh)
                        {
                            m_2d[i+n][j+n2] = true;
                        }
                    }
                    return true;
                }
            }
        }
        return false;
    }

    uint64_t m_area;
    uint64_t m_available_area;
    std::vector<std::vector<bool>> m_2d;
};


class Day12 : public Solver
{
public:
    Day12()
    {
        auto input = parse_input(load_inputs("input_files/day12.txt"sv));
        m_shapes = input.first;
        m_spaces = input.second;
    }
    
    uint64_t solve() final
    {
        uint32_t possible = 0;
        for(auto [tester, fillings] : m_spaces)
        {
            if(fillings.size() != m_shapes.size())
            {
                std::println("size mismatch");
                throw "size mismatch";
            }
            bool fillable = true;
            
            for(size_t index = 0; index<fillings.size() && fillable; index++)
            {
                for(uint32_t i = 0; i < fillings[index] && fillable; i++)
                {
                    fillable &= tester.add_shape();
                }
            }

            if(fillable)
            {
                possible++;
            }
        }
        uint64_t result = possible;
        return result;
    }
    
    uint64_t solve2() final
    {
        return 0;
    }

private:


    std::pair<std::array<uint8_t, 6>, std::vector<std::pair<FillerTest, std::vector<uint32_t>>>> parse_input(auto const &input)
    {
        std::array<uint8_t, 6> shapes{0,0,0,0,0,0};
        std::vector<std::pair<FillerTest, std::vector<uint32_t>>> spaces;
        uint8_t current_index=0xFF;
        bool move_to_spaces=false;
        for(auto const& line: input)
        {
            if(isdigit(line[0]))
            {
                if(!move_to_spaces)
                {
                    current_index = line[0]-'0';
                }
                else
                {
                    auto tokens = tokenize(line, ':');
                    auto dimensions = tokenize(tokens[0], 'x');
                    auto base = std::stoull(dimensions[0]);
                    auto heigth = std::stoull(dimensions[1]);
                    tokens[1].erase(0,1);
                    auto fillings_s = tokenize(tokens[1], ' ');
                    std::vector<uint32_t> fillings;
                    std::transform(fillings_s.begin(), fillings_s.end(), std::back_insert_iterator(fillings), [](std::string const& c){return std::stoul(c);});
                    spaces.push_back({FillerTest(base, heigth), fillings});
                }
            }
            else if(line != "" && current_index != 0xFF)
            {
                shapes[current_index] += std::ranges::count(line, '#');
            }
            else if(line == "" && current_index == 5)
            {
                move_to_spaces = true;
            }
        }
        return std::pair<std::array<uint8_t, 6>, std::vector<std::pair<FillerTest, std::vector<uint32_t>>>>{shapes, spaces};
    }

    std::array<uint8_t, 6> m_shapes;
    std::vector<std::pair<FillerTest, std::vector<uint32_t>>> m_spaces;
};