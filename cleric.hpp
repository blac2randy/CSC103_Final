#pragma once
#include "hp.hpp"
#include "statsblock.hpp"

class Cleric : public hp, public StatBlock {
    
public: 
    static const hptype HPGROWTH = (hptype)13u;
    static const stattype BASESTR = (stattype)2u;
    static const stattype BASEINT = (stattype)3u;
    Cleric () : hp(HPGROWTH, HPGROWTH), StatBlock(BASESTR, BASEINT) {};


    private:
    
};