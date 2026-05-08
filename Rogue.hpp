#pragma once
#include "hp.hpp"
#include "statsblock.hpp"

class Rogue : public hp, public StatBlock {
    
public: 
    static const hptype HPGROWTH = (hptype)10u;
    static const stattype BASESTR = (stattype)3u;
    static const stattype BASEINT = (stattype)2u;
    Rogue () : hp(HPGROWTH, HPGROWTH), StatBlock(BASESTR, BASEINT) {};


    private:
    
};