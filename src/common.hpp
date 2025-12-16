#pragma once
#include <print>
#include <thread>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <list>
#include <map>
#include <tuple>
#include <iostream>
#include <random>
#include <cstdint>
#include <math.h>
#include <fstream>
#include <ranges>
#include <algorithm>
#include <memory>
#include <optional>
#include <bitset>

using namespace std::string_view_literals;

void trim(std::string& s) {
    s.erase(
        std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(),
        s.end()
    );

    s.erase(
        s.begin(),
        std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        })
    );
}

std::vector<std::string> tokenize(const std::string& str, char sep) {
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t end = str.find(sep);
    while (end != std::string::npos) {
        tokens.push_back(str.substr(start, end - start));//push substring till separator    
        start = end + 1;//skip separator 
        end = str.find(sep, start);
    }
    tokens.push_back(str.substr(start));//push back remaining
    return tokens;
}

std::vector<std::string> load_inputs(std::string_view filename)
{
    std::vector<std::string> inputs;
    std::ifstream file(filename.data());
    if(!file.is_open())
    {
        std::println("Error openening file {}", filename.data());
        throw "Error open file";
    }
    std::string str;    
    while (std::getline(file, str))
    {
        inputs.push_back(str);
    }
    return inputs;
}

class Solver
{
public:
    virtual uint64_t solve() = 0;
    virtual uint64_t solve2() = 0;
};