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

/***Remember to cite ChatGPT May 12 2026, How to build a template that prints for 
different encounters ***/

void printBattleScenery(vector<string> sceneryLines, int turn) {
    if (sceneryLines.size() == 0) {
        return;
    }
    int index = (turn - 1) % sceneryLines.size();
    slowPrintLine("\n" + sceneryLines[index], 12);
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

//Battle Function start
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

        printBattleScenery(sceneryLines, turn);

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
                cout << "Your damage increases by " << damageBoostPercent
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
                cout << "\nYour defense is boosted!\n";
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
//Battle Function end

template <typename PlayerType>
void runEncounter(PlayerType& player, vector<Skill> playerSkills, string className,
                  Monster enemy, string encounterTitle, string introText,
                  vector<string> sceneryLines) {
    cout << "\n===== " << encounterTitle << " =====\n";
    slowPrintLine(introText, 15);

    battle(player, enemy, playerSkills, className, sceneryLines);
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
    vector<string> sceneryLines;

    sceneryLines.push_back("The carriage wheels creak behind you as dust rises from the road.");
    sceneryLines.push_back("Able grips the reins tightly while goblins spread across the path.");
    sceneryLines.push_back("One goblin kicks dirt toward the carriage and laughs.");
    sceneryLines.push_back("The horses panic, pulling against their harnesses.");
    sceneryLines.push_back("The forest around the road grows quiet.");
    sceneryLines.push_back("Only the scrape of crude goblin blades breaks the silence.");
    sceneryLines.push_back("Able shouts from behind you, \"Don't let them surround us!\"");
    sceneryLines.push_back("A cold wind cuts across the road.");
    runEncounter(
        player,
        playerSkills,
        className,
        createFirstGoblin(),
        "FIRST ENCOUNTER: ROAD AMBUSH",
        "The goblin steps forward, dragging its rusty dagger across the dirt. Able backs toward the carriage and shouts, \"Now would be a good time to remember how to fight!\"",
        sceneryLines
    );
}

//Able's shop
template <typename PlayerType>
void ableShop(PlayerType& player) {
    int choice;

    while (true) {
        slowPrint("Take whatever you need,", 15);
        cout << "\n===== ABLE'S SHOP =====\n";
        cout << "Gold: " << player.getGold() << "\n\n";

        cout << "1. Buy Health Potion - 10 gold\n";
        cout << "2. Leave Shop\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (player.spendGold(10)) {
                player.addItem("Health Potion");
                cout << "\nAble hands you a Health Potion.\n";
                cout << "\"Use it when things get ugly,\" he says.\n";
            }
            else {
                cout << "\nYou do not have enough gold.\n";
            }
        }
        else if (choice == 2) {
            cout << "\nYou step away from Able's supplies.\n";
            return;
        }
        else {
            cout << "\nInvalid choice.\n";
        }
    }
}

//Resting 
template <typename PlayerType>
void restCamp(PlayerType& player, string locationName, string sceneryText, string ableDialogue, string className) {
    int choice;

    cout << "\n===== CAMP: " << locationName << " =====\n";
    slowPrintLine(sceneryText, 15);
    slowPrintLine("Able guides the carriage off the road and checks the supplies.", 15);

    while (true) {
        cout << "\nWhat would you like to do?\n";
        cout << "1. Rest\n";
        cout << "2. Talk to Able\n";
        cout << "3. Shop with Able\n";
        cout << "4. View Stats\n";
        cout << "5. View Inventory\n";
        cout << "6. Continue\n";
        cout << "Enter choice: ";

        cin >> choice;

        if (choice == 1) {
            player.heal(player.getMaxHP());

            cout << "\nYou rest beside the carriage.\n";
            cout << "Your HP has been restored to "
                 << player.getCurrentHP() << "/" << player.getMaxHP() << ".\n";
        }
        else if (choice == 2) {
            slowPrintLine("\nAble leans against the carriage and looks toward the road ahead.", 15);
            slowPrintLine(ableDialogue, 15);
        }
        else if (choice == 3) {
            ableShop(player);
        }
        else if (choice == 4) {
            showBattleStats(player, className);
        }
        else if (choice == 5) {
            showBattleInventory(player);
        }
        else if (choice == 6) {
            slowPrintLine("\nYou climb back into the carriage. The journey continues.", 15);
            return;
        }
        else {
            cout << "\nInvalid choice. Please choose 1-6.\n";
        }
    }
}
