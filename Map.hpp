#ifndef MAP_HPP
#define MAP_HPP

#include <map>
#include <vector>
#include <string>
#include <iostream>

namespace ariel {

struct Settlement {
    std::vector<std::pair<std::string, int>> hexagons;
    std::vector<int> neighbors;
};

class Map {
private:
    std::map<int, Settlement> settlements;

public:
    Map();
    Settlement getSettlement(int id) const;
    void printBoard() const;
};

}

#endif // MAP_HPP
