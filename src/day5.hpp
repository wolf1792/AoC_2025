#include "common.hpp"

class Day5 : public Solver
{
public:
    Day5()
    {
        auto const inputs = load_inputs("input_files/day5.txt"sv);
        auto [s_ranges, ids] = parse_input(inputs);
        m_ids = ids;
        m_ranges = parse_ranges(s_ranges);
    }
    
    std::pair<std::vector<std::string>, std::vector<std::string>> parse_input(auto const& input)
    {
        std::pair<std::vector<std::string>, std::vector<std::string>> inputs;
        bool blank_found = false;
        for(auto const& str:input)
        {
            if(str=="")
            {
                blank_found = true;
                continue;
            }
            if(!blank_found)
                inputs.first.push_back(str);
            else
                inputs.second.push_back(str);
        }
        return inputs;
    }
    
    std::vector<std::pair<uint64_t, uint64_t>> parse_ranges(const std::vector<std::string>& s_ranges)
    {
        std::vector<std::pair<uint64_t, uint64_t>> ranges;
        for(const auto& s_range : s_ranges)
        {
            auto tokens = tokenize(s_range, '-');
            if(tokens.size() != 2)
                throw std::runtime_error("Invalid range format");
            uint64_t start = std::stoull(tokens[0]);
            uint64_t end = std::stoull(tokens[1]);
            ranges.emplace_back(start, end);
        }
        return ranges;
    }

    static bool is_fresh(const std::vector<std::pair<uint64_t, uint64_t>>& range, uint64_t id)
    {
        for(const auto& [start, end] : range)
        {
            if(id >= start && id <= end)
            {
                return true;
            }
        }
        return false;
    }

    uint64_t solve() final
    {
        uint64_t result = 0;
        for(const auto& s_id : m_ids)
        {
            uint64_t id = std::stoull(s_id);
            if(is_fresh(m_ranges, id))
            {
                result ++;
                continue;
            }
        }

        return result;
    }
    

    std::vector<std::pair<uint64_t, uint64_t>> merge_ranges(const std::vector<std::pair<uint64_t, uint64_t>>& s_ranges)
    {
        if(s_ranges.empty())
            return {};
        std::vector<std::pair<uint64_t, uint64_t>> sorted_ranges = s_ranges;
        std::sort(sorted_ranges.begin(), sorted_ranges.end());
        std::vector<std::pair<uint64_t, uint64_t>> merged;
        auto [current_start, current_end] = sorted_ranges[0];
        for(size_t i = 1; i < sorted_ranges.size(); ++i)
        {
            auto [next_start, next_end] = sorted_ranges[i];
            if(next_start <= current_end + 1)
            {
                current_end = std::max(current_end, next_end);
            }
            else
            {
                merged.emplace_back(current_start, current_end);
                current_start = next_start;
                current_end = next_end;
            }
        }
        merged.emplace_back(current_start, current_end);
        return merged;
    }

    uint64_t solve2() final
    {   
        uint64_t result = 0;
        auto const merged_ranges = merge_ranges(m_ranges);
        for(const auto& [start, end] : merged_ranges)
        {
            result += (end - start + 1);
        }
        return result;
    }
private:
    std::vector<std::string> m_ids;
    std::vector<std::pair<uint64_t, uint64_t>> m_ranges;
};