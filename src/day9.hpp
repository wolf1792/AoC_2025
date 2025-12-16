#include "common.hpp"

class Day9 : public Solver
{
struct point {
    int64_t x;
    int64_t y;
};
public:
    Day9()
    {
        m_inputs = parse_input(load_inputs("input_files/day9.txt"sv));
    }

    uint64_t solve() final
    {
        uint64_t max_area = 0;
        for (size_t i = 0; i < m_inputs.size(); ++i) {
            for (size_t j = i + 1; j < m_inputs.size(); ++j) {
                uint64_t area = rectangle_area(m_inputs[i], m_inputs[j]);
                if (area > max_area) {
                    max_area = area;
                }
            }
        }
        return max_area;
    }
    uint64_t solve2()
    {
        uint64_t maxArea = 0;
        //loop all possible vertexes combinations
        for (size_t i = 0; i < m_inputs.size(); i++) {
            for (size_t j = i + 1; j < m_inputs.size(); j++) {
                point pA = m_inputs[i];
                point pC = m_inputs[j];

                int64_t width = abs(pA.x - pC.x) +1;
                int64_t height = abs(pA.y - pC.y) +1;
                uint64_t area = width * height;

                if (area <= maxArea) 
                    continue;//let's skip if we found a better rect already

                point pB = {pA.x, pC.y};
                point pD = {pC.x, pA.y};

                if (isValidRectangle(m_inputs, pA, pB, pC, pD)) {
                    maxArea = area;
                }
            }
        }
        return maxArea;
    }

private:
    static uint64_t rectangle_area(point const& p1, point const& p2)
    {
        return (std::max(p1.x, p2.x) - std::min(p1.x, p2.x) + 1) *
            (std::max(p1.y, p2.y) - std::min(p1.y, p2.y) + 1);
    }

    std::vector<point> parse_input(auto const& input)
    {
        std::vector<point> points;
        for (auto const& line : input) {
            auto tokens = tokenize(line, ',');
            if (tokens.size() != 2) {
                continue;
            }
            point p{.x=std::stoll(tokens[0]), 
                    .y = std::stoll(tokens[1])};
            points.push_back(p);
        }
        return points;
    }
    

    //check if point q lays on the segment pr
    bool onSegment(point p, point q, point r) {
        return q.x <= std::max(p.x, r.x) && q.x >= std::min(p.x, r.x) &&
            q.y <= std::max(p.y, r.y) && q.y >= std::min(p.y, r.y);
    }

    //line ab intersect line cd?
    bool doIntersect(point a, point b, point c, point d) 
    {
        auto const denominator = ((d.y - c.y) * (b.x - a.x) - (d.x - c.x) * (b.y - a.y));
        if (denominator == 0) {
            return false; // Lines are parallel
        }

        double ua = double((d.x - c.x) * (a.y - c.y) - (d.y - c.y) * (a.x - c.x)) / denominator;
        double ub = double((b.x - a.x) * (a.y - c.y) - (b.y - a.y) * (a.x - c.x)) / denominator;

        // is the intersection along the segments
        if (ua <= 0 || ua >= 1 || ub <= 0 || ub >= 1) {
            return false;
        }
        
        return true;
    }
    
    // Ray Casting algorithm to check if p is inside polygon
    bool isInside(const std::vector<point>& polygon, point p) {
        int n = polygon.size();
        if (n < 3) return false;
        
        int count = 0;
        for (int i = 0; i < n; i++) { //loop all sides
            point p1 = polygon[i];
            point p2 = polygon[(i + 1) % n];
            if (onSegment(p1, p, p2)) {
                return true; //lays on a side => inside
            }
            // Ray Casting algorithm
            if (((p1.y <= p.y && p2.y > p.y) || (p2.y <= p.y && p1.y > p.y)) && 
                (p.x < (p2.x - p1.x) * (p.y - p1.y) / (p2.y - p1.y) + p1.x)) {
                count++;
            }
        }
        
        return count % 2 == 1; // Dispari = interno
    }
    
    bool isValidRectangle(const std::vector<point>& poly, point p1, point p2, point p3, point p4) {
        //All points need to be inside the polygon
        if (!isInside(poly, p1) || !isInside(poly, p2) || 
            !isInside(poly, p3) || !isInside(poly, p4))
        {
            return false;
        }

        //verify to have no intersection between polygon sides and rectagne sides
        std::vector<point> rectpoints = {p1, p2, p3, p4};
        int n = poly.size();        
        for (int i = 0; i < 4; i++) {
            point rStart = rectpoints[i];
            point rEnd = rectpoints[(i + 1) % 4];
            
            for (int j = 0; j < n; j++) {
                point pStart = poly[j];
                point pEnd = poly[(j + 1) % n];
                
                if (doIntersect(rStart, rEnd, pStart, pEnd)) {
                    return false;
                }
            }
        }
        return true;
    }

    std::vector<point> m_inputs;
};