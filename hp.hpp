#pragma once
#include <iostream>
#include "hitpointtype.hpp"
using namespace std;

class Health {
public:
    // reuturns true if set successfully
    // Health pool setup, Health crash prevention

    bool setMaxHp(hptype new_max_hp) {
        if (new_max_hp < 1)
        return false;

        MaxHP = new_max_hp;

        if (CurrentHP > MaxHP)
        CurrentHP = MaxHP;

        return true;
    }

    void takeDamage(hptype damage) {
        if (damage > CurrentHP){
        CurrentHP = 0;
        return;
        }
        CurrentHP -= damage;
    }

    void heal(hptype amount) {
        
    }

   

private:
    hptype ShieldHP;
    hptype CurrentHP;
    hptype MaxHP;
};