#include "common.hpp"

class Day8 : public Solver
{
    struct point {
        int64_t x;
        int64_t y;
        int64_t z;
    };
public:
    Day8()
    {
        m_inputs = parse_input(load_inputs("input_files/day8.txt"sv));
        m_distances = calculate_all_distances();
    }
    uint64_t solve() final
    {
        std::vector<std::set<size_t>> circuits;        
        uint64_t loop = 0;
        for(auto const& [dist, indexes] : m_distances) {
            auto const& [point1_index, point2_index] = indexes;
            auto const& [circuit_point1_index, circuit_point2_index] = find_circuits(circuits, point1_index, point2_index);
            merge_or_add_circuits(circuits, circuit_point1_index, circuit_point2_index, point1_index, point2_index);

            loop++;
            if(loop >= 1000) {  
                break;
            }
        }
        
        // Find greatest circuit size and erase that circuit from circuits => 3 times.
        uint64_t result = 1;
        for(int i=0; i<3; ++i) {
            size_t max_size = 0;
            size_t max_index = 0;
            for (size_t i = 0; i < circuits.size(); ++i) {
                if (circuits[i].size() > max_size) {
                    max_size = circuits[i].size();
                    max_index = i;
                }
            }
            circuits.erase(circuits.begin() + max_index);
            result *= max_size;
        }

        return result;
    }

    uint64_t solve2()
    {
        std::vector<std::set<size_t>> circuits;        
        uint64_t result = 1;
        for(auto const& [dist, indexes] : m_distances) {
            auto const& [point1_index, point2_index] = indexes;
            auto const& [circuit_point1_index, circuit_point2_index] = find_circuits(circuits, point1_index, point2_index);
            merge_or_add_circuits(circuits, circuit_point1_index, circuit_point2_index, point1_index, point2_index);

            if(circuits.size() == 1
                && circuits[0].size() == m_inputs.size()) {
                result = m_inputs[point1_index].x*m_inputs[point2_index].x;
                break;
            }
        }
        
        return result;
    }
private:
    static std::vector<point> parse_input(auto const& input)
    {
        std::vector<point> points;
        for (auto const& line : input) {
            auto tokens = tokenize(line, ',');
            if (tokens.size() != 3) {
                continue;
            }
            point p{.x=std::stoll(tokens[0]), 
                    .y = std::stoll(tokens[1]), 
                    .z = std::stoll(tokens[2])};
            points.push_back(p);
        }
        return points;
    }

    static double distance(point const& a, point const& b) 
    {
        return sqrt((pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + pow((a.z - b.z), 2)));
    }

    std::map<double, std::pair<size_t, size_t>> calculate_all_distances() const
    {
        std::map<double, std::pair<size_t, size_t>> distances;
        for (size_t i = 0; i < m_inputs.size(); ++i) {
            for (size_t j = i + 1; j < m_inputs.size(); ++j) {
                
                double dist = distance(m_inputs[i], m_inputs[j]);
                distances.insert({dist, {i, j}});
            }
        }
        return distances;
    }

    static std::pair<std::optional<uint64_t>, std::optional<uint64_t>> 
    find_circuits(std::vector<std::set<size_t>> const& circuits, size_t const point1_index, size_t const point2_index)
    {
        std::optional<uint64_t> circuit_point1_index;
        std::optional<uint64_t> circuit_point2_index;
        for(auto const& [index, circuit] : std::views::enumerate(circuits)) {
            if (circuit.contains(point1_index) && !circuit_point1_index.has_value()) {
                circuit_point1_index = index;
                continue;
            }
            if (circuit.contains(point2_index)) {
                circuit_point2_index = index;
            }
        }
        return {circuit_point1_index, circuit_point2_index};
    }

    static void merge_or_add_circuits(std::vector<std::set<size_t>>& circuits, std::optional<uint64_t> circuit_point1_index, 
                            std::optional<uint64_t> circuit_point2_index, size_t const point1_index, size_t const point2_index)
    {
        if(circuit_point1_index.has_value() && circuit_point2_index.has_value()) {
            //merge circuits
            if(*circuit_point1_index != *circuit_point2_index) {
                circuits[*circuit_point1_index].merge(circuits[*circuit_point2_index]);
                circuits.erase(circuits.begin() + *circuit_point2_index);
            }
        } else if(circuit_point1_index.has_value()) {
            circuits[*circuit_point1_index].insert(point2_index);
        }
        else if(circuit_point2_index.has_value()) {
            circuits[*circuit_point2_index].insert(point1_index);
        } else {
            circuits.push_back({point1_index, point2_index});
        }
    }

    std::vector<point> m_inputs;
    std::map<double, std::pair<size_t, size_t>> m_distances;
};