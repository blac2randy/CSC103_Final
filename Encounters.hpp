#pragma once
#include <iostream>
#include <string>
#include "PlayerClasses.hpp"
#include "Monster.hpp"
#include "Skills.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//Prints changing scenery based on the battle turn, rotates the text to fit imagery
void FirstEncount(int turn) {

    int scene = turn % 5;

    if (scene == 1) {
        cout << "\nThe carriage wheels creak behind you as dust rises from the road.\n";
        cout << "Able grips the reins tightly while goblins spread across the path.\n";
    }
    else if (scene == 2) {
        cout << "\nOne goblin kicks dirt toward the carriage and laughs.\n";
        cout << "The horses panic, pulling against their harnesses.\n";

    }
    else if (scene == 3) {
        cout << "\nThe forest around the road grows quiet.\n";
        cout << "Only the scrape of crude goblin blades breaks the silence.\n";
    }
    else if (scene == 4) {
        cout << "\nAble shouts from behind you, \"Don't let them surround us!\"\n";
        cout << "The goblins begin circling closer.\n";

    }
    else {
        cout << "\nA cold wind cuts across the road.\n";
        cout << "The goblin bares its teeth and tightens its grip on the dagger.\n";

    }

}
template <typename PlayerType>

void showBattleStats(PlayerType& player, string className) {

    cout << "\n===== PLAYER STATS =====\n";
    cout << "Class: " << className << endl;
    cout << "Level: " << player.getLevel() << endl;
    cout << "XP: " << player.getXP() << endl;
    cout << "HP: " << player.getCurrentHP() << "/" << player.getMaxHP() << endl;
    cout << "Strength: " << player.getStrength() << endl;
    cout << "Intellect: " << player.getIntellect() << endl;

}
// =============================

void showBattleInventory() {
    cout << "\n===== INVENTORY =====\n";
    cout << "Inventory system coming soon.\n";
    cout << "For now, no usable items are connected yet.\n";
}

