#pragma once

#include <iostream>
#include <vector>

#include "player.hpp"
#include "utility.hpp"

using namespace std;

struct ConsolePlayer : public Player {
    ConsolePlayer(ostream& os, istream& is) : os(os), is(is) {}

    virtual Point play(const vector<Point>& playerStones, const vector<Point>& opponentStones) {
        os << "Your stones are ";
        print(playerStones, os);
        os << " opponent stones are ";
        print(opponentStones, os);
        os << "." << endl
           << "Your move: ";
        return Point::loadPoint(is);
    }

   private:
    ostream& os;
    istream& is;
};
