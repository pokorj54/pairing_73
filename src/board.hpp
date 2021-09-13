#pragma once

#include <string>
#include <vector>

#include "point.hpp"
#include "utility.hpp"

/**
 * @brief Class that holds information about moves made as well as their order.
 * 
 */
struct Board {
    /**
     * @brief Returns the number of crosses and circles made 
     * 
     * @return size_t number of plies made 
     */
    size_t pliesMade() const;

    /**
     * @brief Adds point to the board. Point has to be different than points added previously. 
     * 
     * @param point  
     */
    void addPly(const Point& point);

    const vector<Point>& getCrosses() const;
    const vector<Point>& getCircles() const;

    std::string toString(char delimiter = ' ') const;

    string nameFile() const {
        return toString('_') + ".txt";
    }

   private:
    vector<Point> crosses, circles;
};
