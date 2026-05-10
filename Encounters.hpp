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
//inventory display
template <typename PlayerType>
void showBattleInventory(PlayerType& player) {
    player.showInventory();
}

template <typename PlayerType>
void battle(PlayerType& player, Monster enemy, vector<Skill> playerSkills, string className) {
    int turn = 1;

    cout << "\n===== BATTLE START =====\n";
    cout << enemy.getName() << " appears!\n";
    cout << enemy.getDescription() << "\n";

    while (player.getCurrentHP() > 0 && !enemy.isDefeated()) {
        cout << "\n==============================\n";
        cout << "TURN " << turn << endl;
        cout << "==============================\n";

        FirstEncount(turn);

        cout << "\n\nYour HP: " << player.getCurrentHP() << "/" << player.getMaxHP() << endl;
        cout << enemy.getName() << " HP: " << enemy.getCurrentHP() << "/" << enemy.getMaxHP() << endl;

        cout << "\nWhat will you do?\n";
        cout << "1. Use Skill\n";
        cout << "2. View Stats\n";
        cout << "3. View Inventory\n";
        cout << "4. Use Item\n";
        cout << "5. Observe Surroundings\n";
        cout << "Enter choice: ";

    //Choice Logic
        int choice;
        cin >> choice;

        bool turnPassed = false;

        if (choice == 1) {
            showAvailableSkills(playerSkills, player.getLevel());

            cout << "Choose skill: ";
            int skillChoice;
            cin >> skillChoice;

            int index = skillChoice - 1;

            if (index >= 0 && index < playerSkills.size() &&
                player.getLevel() >= playerSkills[index].unlockLevel) {

                int damage = calculateSkillDamage(
                    playerSkills[index],
                    player.getStrength(),
                    player.getIntellect()
                );

                cout << "\nYou use " << playerSkills[index].name << "!\n";
                cout << "You deal " << damage << " damage to " << enemy.getName() << ".\n";

                enemy.takeDamage(damage);
            }
            else {
                cout << "\nInvalid or locked skill. You hesitate and lose your chance to attack.\n";
            }

            turnPassed = true;
        }
        else if (choice == 2) {
            showBattleStats(player, className);
        }

        else if (choice == 3) {
            showBattleInventory(player);
        }

        else if (choice == 4) {

            showBattleInventory(player);
            cout << "Choose an item to use: ";
            int itemChoice;
            cin >> itemChoice;
            bool usedItem = player.useItem(itemChoice);

            if (usedItem) {
                cout << "Current HP: " << player.getCurrentHP()
                << "/" << player.getMaxHP() << endl;
                turnPassed = true;
            }
            else {
                cout << "No item was used.\n";
            }
        }

        else if (choice == 5) {
            cout << "\nYou scan the road carefully.\n";
            cout << "There are more goblins nearby, but only one is attacking first.\n";
            cout << "Able stays near the carriage, waiting for an opening.\n";
            turnPassed = true;
        }
        else {
            cout << "\nInvalid choice. You hesitate.\n";
            turnPassed = true;
        }

        if (enemy.isDefeated()) {
            break;
        }

        if (turnPassed) {
            int enemyDamage = enemy.getStrength();

            cout << "\n" << enemy.getName() << " lunges forward and attacks!\n";
            cout << enemy.getName() << " deals " << enemyDamage << " damage.\n";

            player.takeDamage(enemyDamage);

            turn++;
        }
    }

    if (player.getCurrentHP() > 0) {
        cout << "\n===== VICTORY =====\n";
        cout << "You defeated " << enemy.getName() << "!\n";

        cout << "\nYou gained " << enemy.getXPReward() << " XP.\n";
        player.gainXP(enemy.getXPReward());

       cout << "You found " << enemy.getGoldReward() << " gold.\n";
       player.gainGold(enemy.getGoldReward());
       cout << "Current Gold: " << player.getGold() << endl;
    }
    else {
        cout << "\n===== DEFEAT =====\n";
        cout << "You collapse beside the carriage.\n";
        cout << "Able shouts your name, but the sound fades into darkness.\n";
    }
}

Monster createFirstGoblin() {
    return Monster(
        "Goblin Scout",
        "A small goblin carrying a rusty dagger. Its eyes dart between you and the carriage.",
        12,
        2,
        0,
        30,
        5
    );
}

template <typename PlayerType>
void firstGoblinEncounter(PlayerType& player, vector<Skill> playerSkills, string className) {
    cout << "\n===== FIRST ENCOUNTER: ROAD AMBUSH =====\n";
    cout << "The goblin steps forward, dragging its rusty dagger across the dirt.\n";
    cout << "Able backs toward the carriage and shouts,\n";
    cout << "\"Now would be a good time to remember how to fight!\"\n";

    Monster goblin = createFirstGoblin();

    battle(player, goblin, playerSkills, className);
}

