#include "common.hpp"

class Day11 : public Solver
{
using graph_t = std::unordered_map<std::string, std::set<std::string>>;
public:
    Day11()
    {
        m_graph = build_graph(load_inputs("input_files/day11.txt"sv));
    }

    uint64_t solve() final
    {
        std::vector<std::string> to_visit{"you"};
        uint64_t out_count = 0;   
        while(!to_visit.empty())
        {
            auto current = to_visit.back();
            to_visit.pop_back();
            if(current=="out")
            {
                out_count++;
            }
            else{          
                auto neighbors = get_neighbors(m_graph, current);
                for (auto const &neighbor : neighbors)
                {
                    
                    to_visit.push_back(neighbor);
                }
            }
        } 
        return out_count;
    }

    auto DFS(std::string const& current, bool dac_visited, bool fft_visited, auto &memo)
    {
        if (memo[{current, dac_visited, fft_visited}] != -1)
        {
            return memo[{current, dac_visited, fft_visited}];
        }
        if (current == "out")
        {
            int64_t visited = (dac_visited && fft_visited) ? 1 : 0;
            memo[{current, dac_visited, fft_visited}] = visited;
            return visited;
        }

        int64_t ret = 0LL;
        for (auto const& neighbor : m_graph[current]) {
            int next_dac = dac_visited;
            int next_fft = fft_visited;
            if (neighbor == "dac")
            {
                next_dac = true;
            }
            else if (neighbor == "fft")
            {
                next_fft = true;
            }

            ret += DFS(neighbor, next_dac, next_fft, memo);
        }
        memo[{current, dac_visited, fft_visited}] = ret;
        return ret;
    }

    uint64_t solve2() final
    {        
        std::map<std::tuple<std::string, bool, bool>, int64_t> memo;
        //initialize memo map
        for (auto const& [node, neighbors] : m_graph) {
        memo[{node, false, false}] = -1;
        memo[{node, true, false}] = -1;
        memo[{node, false, true}] = -1;
        memo[{node, true, true}] = -1;
        for (auto const& neighbor : neighbors) {
            memo[{neighbor, false, false}] = -1;
            memo[{neighbor, true, false}] = -1;
            memo[{neighbor, false, true}] = -1;
            memo[{neighbor, true, true}] = -1;
        }
        }
        
        uint64_t result = DFS("svr", false, false, memo);
        return result;
    }

private:
    graph_t build_graph(auto const &input)
    {
        graph_t graph;
        for (auto const &line : input)
        {
            auto parts = tokenize(line, ':');
            auto input = parts[0];
            auto outputs = tokenize(parts[1], ' ');
            std::set<std::string> output_set{outputs.begin(), outputs.end()};
            output_set.erase("");
            graph[input] = output_set;
        }
        return graph;
    }
    std::set<std::string> get_neighbors(graph_t const &graph, std::string const &node)
    {
        auto it = graph.find(node);
        if (it != graph.end())
        {
            return it->second;
        }
        return {};
    }

    graph_t m_graph;
};