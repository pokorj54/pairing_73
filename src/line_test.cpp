#include "line.hpp"

#include <cassert>
using namespace std;

int main(void) {
    assert(Line::isConstant(0));
    assert(Line::isConstant(1));
    assert(Line::isConstant(2));
    assert(Line::isConstant(3));
    assert(Line::isConstant(4));
    assert(Line::isConstant(5));
    assert(Line::isConstant(6));

    assert(!Line::isConstant(Line::decreasing));
    assert(!Line::isConstant(Line::increasing));

    assert(Line::flipDirection(0) == 0);
    assert(Line::flipDirection(1) == 1);
    assert(Line::flipDirection(2) == 2);
    assert(Line::flipDirection(3) == 3);
    assert(Line::flipDirection(4) == 4);
    assert(Line::flipDirection(5) == 5);
    assert(Line::flipDirection(6) == 6);

    assert(Line::flipDirection(Line::decreasing) == Line::increasing);
    assert(Line::flipDirection(Line::increasing) == Line::decreasing);

    // number of all lines in n^d hypercube is ((n+2)^d - n^d)/2
    assert(Line::generateAllCanonicalLines().size() == (9 * 9 * 9 - 7 * 7 * 7) / 2);

    assert(Line(0, 0, Line::increasing).getFlippedLine() == Line(0, 0, Line::decreasing));
    assert(Line(1, Line::decreasing, 5).getFlippedLine() == Line(1, Line::increasing, 5));
    assert(Line(2, Line::decreasing, Line::decreasing).getFlippedLine() == Line(2, Line::increasing, Line::increasing));
    assert(Line(Line::decreasing, 3, Line::increasing).getFlippedLine() == Line(Line::increasing, 3, Line::decreasing));
    assert(Line(Line::increasing, Line::increasing, Line::decreasing).getFlippedLine() == Line(Line::decreasing, Line::decreasing, Line::increasing));

    vector<Line> lines = {
        Line(0, 0, Line::increasing),
        Line(1, Line::decreasing, 5),
        Line(2, Line::decreasing, Line::decreasing),
        Line(Line::decreasing, 3, Line::increasing),
        Line(Line::increasing, Line::increasing, Line::decreasing)};
    for (const Line& line : lines) {
        Line flipped = line.getFlippedLine();
        assert(!(line == flipped));
        assert(line.isCanonical() != flipped.isCanonical());
    }

    assert(Line(0, 0, Line::increasing) == Line(0, 0, Line::increasing));
    assert(Line(Line::increasing, Line::decreasing, 6) == Line(Line::increasing, Line::decreasing, 6));
    assert(!(Line(Line::increasing, Line::decreasing, 2) == Line(Line::decreasing, Line::decreasing, 2)));
    assert(!(Line(Line::decreasing, 3, Line::increasing) == Line(Line::increasing, 3, Line::decreasing)));
    assert(!(Line(Line::increasing, 0, 1) == Line(0, 1, Line::increasing)));

    assert(Line(Line::increasing, 3, 3).containsPoint(Point(3, 3, 3)));
    assert(Line(Line::increasing, 3, 3).containsPoint(Point(6, 3, 3)));
    assert(!Line(Line::increasing, 3, 3).containsPoint(Point(1, 1, 1)));
    assert(Line(0, Line::decreasing, Line::increasing).containsPoint(Point(0, 0, 6)));
    assert(Line(0, Line::decreasing, Line::increasing).containsPoint(Point(0, 3, 3)));
    assert(Line(0, Line::decreasing, Line::increasing).containsPoint(Point(0, 5, 1)));
    assert(!Line(0, Line::decreasing, Line::increasing).containsPoint(Point(0, 1, 1)));

    for (const Line& line : lines) {
        vector<Point> containedPoints = line.getPointsOnLine();
        assert(containedPoints.size() == 7);
        for (const Point& point : containedPoints) {
            assert(line.containsPoint(point));
        }
    }
    return 0;
}