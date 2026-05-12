#pragma once
#include <iostream>
#include <string>
#include "PlayerClasses.hpp"
#include "Monster.hpp"
#include "Skills.hpp"
#include <iostream>
#include <string>
#include <vector>
#include "TextHelp.hpp" 
using namespace std;

// Prints changing scenery based on the battle turn, rotates the text to fit imagery
void FirstEncount(int turn) {
    int scene = turn % 5;

    if (scene == 1) {
        slowPrintLine("\nThe carriage wheels creak behind you as dust rises from the road.", 12);
        slowPrintLine("Able grips the reins tightly while goblins spread across the path.", 12);
    }
    else if (scene == 2) {
        slowPrintLine("\nOne goblin kicks dirt toward the carriage and laughs.", 12);
        slowPrintLine("The horses panic, pulling against their harnesses.", 12);
    }
    else if (scene == 3) {
        slowPrintLine("\nThe forest around the road grows quiet.", 12);
        slowPrintLine("Only the scrape of crude goblin blades breaks the silence.", 12);
    }
    else if (scene == 4) {
        slowPrintLine("\nAble shouts from behind you, \"Don't let them surround us!\"", 12);
        slowPrintLine("The goblins begin circling closer.", 12);
    }
    else {
        slowPrintLine("\nA cold wind cuts across the road.", 12);
        slowPrintLine("The goblin bares its teeth and tightens its grip on the dagger.", 12);
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
    int damageBoostPercent = 0;
    int damageBoostTurns = 0;
    int damageReductionPercent = 0;
    int damageReductionTurns = 0;

    cout << "\n===== BATTLE START =====\n";
    slowPrintLine(enemy.getName() + " appears!", 15);
    slowPrintLine(enemy.getDescription(), 15);

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

    if (index >= 0 && index < static_cast<int>(playerSkills.size()) &&
        player.getLevel() >= playerSkills[index].unlockLevel) {

        if (playerSkills[index].currentCooldown > 0) {
            cout << "\n" << playerSkills[index].name << " is on cooldown for "
                << playerSkills[index].currentCooldown << " more turn(s).\n";
        }
        else {
            Skill chosenSkill = playerSkills[index];

            if (chosenSkill.effectType == "BOOST_DAMAGE") {
                damageBoostPercent = chosenSkill.value;
                damageBoostTurns = chosenSkill.duration;

                cout << "\nYou use " << chosenSkill.name << "!\n";
                cout << "Your skill damage increases by " << damageBoostPercent
                    << "% for " << damageBoostTurns << " turns.\n";
            }
            else if (chosenSkill.effectType == "REDUCE_DAMAGE_TAKEN") {
                damageReductionPercent = chosenSkill.value;
                damageReductionTurns = chosenSkill.duration;

                cout << "\nYou use " << chosenSkill.name << "!\n";
                cout << "Enemy damage is reduced by " << damageReductionPercent
                    << "% for " << damageReductionTurns << " turns.\n";
            }
            else {
                int damage = calculateSkillDamage(
                    chosenSkill,
                    player.getStrength(),
                    player.getIntellect(),
                    enemy.getMaxHP()
                );
                if (damageBoostTurns > 0) {
                    damage = damage * (100 + damageBoostPercent) / 100;
                }

                cout << "\nYou use " << chosenSkill.name << "!\n";
                if (chosenSkill.effectType == "MULTI_HIT") {
                    cout << "You strike " << chosenSkill.value << " times!\n";
                }

                cout << "You deal " << damage << " damage to " << enemy.getName() << ".\n";
                enemy.takeDamage(damage);
            }
        playerSkills[index].currentCooldown = playerSkills[index].cooldown;
    }
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
            slowPrintLine("\nYou scan the road carefully.", 12);
            slowPrintLine("There are more goblins nearby, but only one is attacking first.", 12);
            slowPrintLine("Able stays near the carriage, waiting for an opening.", 12);
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
            if (damageReductionTurns > 0) {
                enemyDamage = enemyDamage * (100 - damageReductionPercent) / 100;
            
                if (enemyDamage < 1) {
                    enemyDamage = 1;
                }
                cout << "\nYour defensive effect reduces the attack!\n";
            }
            cout << "\n" << enemy.getName() << " lunges forward and attacks!\n";
            cout << enemy.getName() << " deals " << enemyDamage << " damage.\n";

            player.takeDamage(enemyDamage);
            //Reduce cooldown timers
            for (int i = 0; i < static_cast<int>(playerSkills.size()); i++) {
                if (playerSkills[i].currentCooldown > 0) {
                    playerSkills[i].currentCooldown--;
                }
            }
            if (damageBoostTurns > 0) {
                damageBoostTurns--;
            }

            if (damageReductionTurns > 0) {
                damageReductionTurns--;
            }
            turn++;
        }
    }

    if (player.getCurrentHP() > 0) {
        cout << "\n===== VICTORY =====\n";
        slowPrintLine("You defeated " + enemy.getName() + "!", 15);

        cout << "\nYou gained " << enemy.getXPReward() << " XP.\n";
        player.gainXP(enemy.getXPReward());

       cout << "You found " << enemy.getGoldReward() << " gold.\n";
       player.gainGold(enemy.getGoldReward());
       cout << "Current Gold: " << player.getGold() << endl;
    }
    else {
        cout << "\n===== DEFEAT =====\n";
        slowPrintLine("You collapse beside the carriage.", 20);
        slowPrintLine("Able shouts your name, but the sound fades into darkness.", 20);
    }
}

Monster createFirstGoblin() {
    return Monster(
        "Goblin Scout",
        "A small goblin carrying a rusty dagger. Its eyes dart between you and the carriage.",
        12,
        2,
        0,
        15,
        5
    );
}

template <typename PlayerType>
void firstGoblinEncounter(PlayerType& player, vector<Skill> playerSkills, string className) {
    cout << "\n===== FIRST ENCOUNTER: ROAD AMBUSH =====\n";
    slowPrintLine("The goblin steps forward, dragging its rusty dagger across the dirt.", 15);
    slowPrintLine("Able backs toward the carriage and shouts,", 15);
    slowPrintLine("\"Now would be a good time to remember how to fight!\"", 15);

    Monster goblin = createFirstGoblin();

    battle(player, goblin, playerSkills, className);
}

