#pragma once

#include <iostream>
#include <vector>

#include "player.hpp"
#include "utility.hpp"

using namespace std;

struct ConsolePlayer : public Player {
    ConsolePlayer(ostream& os, ostream& pc_format, istream& is) : os(os), pc_format(pc_format), is(is) {}

    virtual Point play(const vector<Point>& playerStones, const vector<Point>& opponentStones) {
        if (opponentStones.size() >= 1) {
            pc_format << opponentStones[opponentStones.size() - 1] << endl;
        }
        os << "Your stones are ";
        print(playerStones, os);
        os << " opponent stones are ";
        print(opponentStones, os);
        os << "." << endl;
        os << "Your move: ";
        return Point::loadPoint(is);
    }

   private:
    ostream& os;
    ostream& pc_format;
    istream& is;
};
