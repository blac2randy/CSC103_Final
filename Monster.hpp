#pragma once
#include <iostream>
#include <string>
#include "hp.hpp"
#include "statsblock.hpp"
using namespace std;

class Monster : public hp, public StatBlock {
private:
    string name;
    string description;
    int xpReward;
    int goldReward; 
    
public:
 public:

    Monster() : hp(1, 1), StatBlock(1, 0) {
        name = "Unknown Monster";
        description = "A strange creature.";
        xpReward = 0;
        goldReward = 0;

    }

    Monster(string monsterName, string monsterDescription,
            hptype monsterHP, stattype monsterStrength, stattype monsterIntellect,
            int rewardXP, int rewardGold)

        : hp(monsterHP, monsterHP), StatBlock(monsterStrength, monsterIntellect) {

        name = monsterName;
        description = monsterDescription;
        xpReward = rewardXP;
        goldReward = rewardGold;

    }
    string getName() {
        return name;
    }

    string getDescription() {
      return description;
    }

    int getXPReward() {
        return xpReward;

    }
    int getGoldReward() {
        return goldReward;

    }
    bool isDefeated() {
        return getCurrentHP() <= 0;

    }

};


  

   