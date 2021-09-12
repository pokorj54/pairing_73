#include "board.hpp"

#include <cassert>

using namespace std;

size_t Board::pliesMade() const {
    return crosses.size() + circles.size();
}

void Board::addPly(const Point& point) {
    assert(!isInVector(crosses, point) && !isInVector(circles, point));
    if (pliesMade() % 2 == 0) {
        crosses.push_back(point);
    } else {
        circles.push_back(point);
    }
}

const vector<Point>& Board::getCrosses() const {
    return crosses;
}

const vector<Point>& Board::getCircles() const {
    return circles;
}

std::string Board::toString(char delimiter) const {
    string result = "";
    for (size_t i = 0; i < crosses.size(); ++i) {
        if (i != 0) {
            result += delimiter;
        }
        result += crosses[i].toString();
        if (i < circles.size()) {
            result += delimiter + circles[i].toString();
        }
    }
    return result;
}
