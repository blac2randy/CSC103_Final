#pragma once
#include "hp.hpp"
#include "statsblock.hpp"

// =============================
// Warrior Class
// Highest HP and strength
// =============================
class Warrior : public hp, public StatBlock {
public:
    static const hptype HPGROWTH = (hptype)19u;
    static const stattype BASESTR = (stattype)4u;
    static const stattype BASEINT = (stattype)1u;

    Warrior() : hp(HPGROWTH, HPGROWTH), StatBlock(BASESTR, BASEINT) {}
};

// =============================
// Wizard Class
// Highest intellect / magic
// =============================
class Wizard : public hp, public StatBlock {
public:
    static const hptype HPGROWTH = (hptype)9u;
    static const stattype BASESTR = (stattype)1u;
    static const stattype BASEINT = (stattype)4u;

    Wizard() : hp(HPGROWTH, HPGROWTH), StatBlock(BASESTR, BASEINT) {}
};

// =============================
// Cleric Class
// Balanced HP and intellect
// =============================
class Cleric : public hp, public StatBlock {
public:
    static const hptype HPGROWTH = (hptype)13u;
    static const stattype BASESTR = (stattype)2u;
    static const stattype BASEINT = (stattype)3u;

    Cleric() : hp(HPGROWTH, HPGROWTH), StatBlock(BASESTR, BASEINT) {}
};

// =============================
// Rogue Class
// Consistent physical damage
// =============================
class Rogue : public hp, public StatBlock {
public:
    static const hptype HPGROWTH = (hptype)10u;
    static const stattype BASESTR = (stattype)3u;
    static const stattype BASEINT = (stattype)2u;

    Rogue() : hp(HPGROWTH, HPGROWTH), StatBlock(BASESTR, BASEINT) {}
};