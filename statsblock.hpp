#pragma once
#include "statstype.hpp"

class StatBlock {
    stattype Strength; 
    stattype Intellect; 

public:
    StatBlock() { 
        Strength =(stattype)1u; 
        Intellect = (stattype)1u;
    }
    explicit StatBlock(stattype s, stattype i) { 
        Strength = s;
        Intellect = i;
    }
    void increaseStrength(stattype amount) {
    Strength += amount;
    }

    void increaseIntellect(stattype amount) {
    Intellect += amount;
    }
    stattype getStrength() { return Strength; }
    stattype getIntellect() { return Intellect; }

};
