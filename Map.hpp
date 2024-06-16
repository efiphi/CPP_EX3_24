#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <unordered_map>
#include <string>

namespace ariel {

struct Settlement {
    std::vector<std::pair<std::string, int>> hexagons; // Pairs of resource and number
    std::vector<int> neighbors;
};

class Map {
private:
    std::unordered_map<int, Settlement> settlements;

public:
    Map();
    const Settlement& getSettlement(int set_id) const;
};

}

#endif // MAP_HPP
