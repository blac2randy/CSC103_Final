#pragma once
#include "hp.hpp"
#include "statsblock.hpp"

class Wizard : public hp, public StatBlock {
    
public: 
    static const hptype HPGROWTH = (hptype)9u;
    static const stattype BASESTR = (stattype)1u;
    static const stattype BASEINT = (stattype)4u;
    Wizard () : hp(HPGROWTH, HPGROWTH), StatBlock(BASESTR, BASEINT) {};


    private:
    
};