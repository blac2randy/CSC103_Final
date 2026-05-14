#pragma once
#include <iostream>
#include <string>
#include "PlayerClasses.hpp"
#include "Monster.hpp"
#include "Skills.hpp"
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

//Item Usage function
template <typename PlayerType>
bool useBattleItem(PlayerType& player, int itemChoice,
                   int& damageBoostPercent, int& damageBoostTurns,
                   int& damageReductionPercent, int& damageReductionTurns) {
    int index = itemChoice - 1;

    if (index < 0 || index >= player.getInventorySize()) {
        cout << "Invalid item choice.\n";
        return false;
    }

    string item = player.getItem(index);

    if (item == "Health Potion") {
        player.heal(10);
        cout << "You used a Health Potion and restored 10 HP.\n";
        player.removeItem(index);
        return true;
    }
    else if (item == "Greater Health Potion") {
        player.heal(25);
        cout << "You used a Greater Health Potion and restored 25 HP.\n";
        player.removeItem(index);
        return true;
    }
    else if (item == "Titan's Blood") {
        damageBoostPercent = 20;
        damageBoostTurns = -1; // rest of battle

        cout << "You drank Titan's Blood.\n";
        cout << "Your skill damage increases by 20% for the rest of the battle.\n";

        player.removeItem(index);
        return true;
    }
    else if (item == "Cursed Beetle Larvae") {
        damageReductionPercent = 20;
        damageReductionTurns = -1; // rest of battle

        cout << "You bit into the Cursed Beetle Larvae.\n";
        cout << "Enemy damage is reduced by 20% for the rest of the battle.\n";

        player.removeItem(index);
        return true;
    }
    else if (item == "Dancer's Talisman") {
        player.heal(30);

        damageBoostPercent = 20;
        damageBoostTurns = -1; // rest of battle

        damageReductionPercent = 20;
        damageReductionTurns = -1; // rest of battle

        cout << "You channel your will into the Dancer's Talisman.\n";
        cout << "You restored 30 HP.\n";
        cout << "Your damage increases by 20% and enemy damage is reduced by 20% for the rest of battle.\n";

        player.removeItem(index);
        return true;
    }

    cout << item << " cannot be used right now.\n";
    return false;
}

//Battle Function start
template <typename PlayerType>
void battle(PlayerType& player, Monster enemy, vector<Skill> playerSkills, string className,vector<string> sceneryLines, string observeText) {
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
            if (damageBoostTurns > 0 || damageBoostTurns == -1) {
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

            bool usedItem = useBattleItem(
                player,
                itemChoice,
                damageBoostPercent,
                damageBoostTurns,
                damageReductionPercent,
                damageReductionTurns
            );

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
            slowPrintLine("\n" + observeText, 12);
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
            if (damageReductionTurns > 0 || damageReductionTurns == -1) {
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

//Encounter System
/* Basically I reworked the first encounter to work as a template for future encounters  */
template <typename PlayerType>
void runEncounter(PlayerType& player, vector<Skill> playerSkills, string className,
                  Monster enemy, string encounterTitle, string introText,
                  vector<string> sceneryLines, string observeText) {
    cout << "\n===== " << encounterTitle << " =====\n";
    slowPrintLine(introText, 15);

    battle(player, enemy, playerSkills, className, sceneryLines, observeText);
}

//List of World one creatures
Monster createGoblin() {
    return Monster(
        "Goblin Scout",
        "A small goblin carrying a rusty dagger. Its eyes dart between you and the carriage.",
        12, //HP
        2,  // Strength
        0,  //Intellect
        15, //XP reward
        5 //Gold
    );
}

Monster createHobgoblin() {
    return Monster(
        "Hobgoblin",
        "A disciplined goblinoid warrior wearing cracked leather armor and a wolf skull helm. He carries a rusted serrated shortsword and a small wooden buckler.",
        20, 
        4,   
        0,   
        20,  
        8    
    );

}
Monster createGoblinShaman() {
    return Monster(
        "Goblin Shaman",
        "A hunched goblin covered in bone charms and faded red paint. Arcane flows sickly through it's crooked staff.",
        24, 
        2,  
        4,  
        25, 
        10  
    );
}
Monster createGoblinChief() {
    return Monster(
        "Goblin Chief",
        "A massive goblin wrapped in armor and animal bones. He carries a heavy cleaver stained of bloof from numerous battles.(Do you even lift bro)",
        40, 
        6,  
        2,  
        35, 
        20 
    );
}

//List of World One Monsters Ecounters
template <typename PlayerType>
void GoblinEncounter(PlayerType& player, vector<Skill> playerSkills, string className) {
    vector<string> sceneryLines;

    sceneryLines.push_back("The carriage wheels creak behind you as dust rises from the road.");
    sceneryLines.push_back("Able grips the reins tightly while goblins spread across the path.");
    sceneryLines.push_back("One goblin kicks dirt toward the carriage and laughs.");
    sceneryLines.push_back("The horses panic, pulling against their harnesses.");
    sceneryLines.push_back("The forest around the road grows quiet.");
    sceneryLines.push_back("Only the scrape of crude goblin blades breaks the silence.");
    sceneryLines.push_back("Able shouts from behind you, \"Don't let them surround us!\"");
    sceneryLines.push_back("A cold wind whistles across the road.");
    runEncounter(
        player,
        playerSkills,
        className,
        createGoblin(),
        "FIRST ENCOUNTER: ROAD AMBUSH",
        "The goblin steps forward, dragging its rusty dagger across the dirt. Able backs toward the carriage and shouts, \"Now would be a good time to remember how to fight!\"",
        sceneryLines,
        "There are more goblins nearby, but only one is attacking first. Able stays near the carriage, waiting for an opening."
    );
}

template <typename PlayerType>
void HobgoblinEncounter(PlayerType& player, vector<Skill> playerSkills, string className) {
    vector<string> sceneryLines;

    sceneryLines.push_back("The forest grows thicker as you move farther from the road.");
    sceneryLines.push_back("Sword marks cut across the bark of nearby trees.");
    sceneryLines.push_back("Half-eaten animals lie near the path, warning you that goblins are close.");
    sceneryLines.push_back("Able keeps one hand near his supplies, watching the bushes carefully.");
    sceneryLines.push_back("The twisted vine trap snaps behind you as the hobgoblin steps forward.");
    sceneryLines.push_back("The hobgoblin taps his wooden buckler with his serrated blade, daring you to move first.");
    runEncounter(
        player,
        playerSkills,
        className,
        createHobgoblin(),
        "SECOND ENCOUNTER: GOBLIN CAMP TRAIL",
        "As you venture deep into the forest, you begin to see signs of a goblin camp: sword marks on trees, half-eaten animals, and crude traps hidden in the brush. Suddenly, your foot catches on a tripwire made of twisted vines. From the bushes steps a hobgoblin wearing leather armor and a wolf skull helm. Able lowers his voice: \"That is no scout. Hobgoblins are trained for war. Prepare yourself.\"",
        sceneryLines,
        "The hobgoblin stands with discipline unlike the scout, that is they seem to actually have thought. His buckler is raised, his blade angled low, and his eyes track your every movement."
    );
}
template <typename PlayerType>
void GoblinShamanEncounter(PlayerType& player, vector<Skill> playerSkills, string className) {
    vector<string> sceneryLines;

    sceneryLines.push_back("The smell of rotting flesh and old bones cuts through the air.");
    sceneryLines.push_back("Small charms made of feathers and teeth hang from the branches.");
    sceneryLines.push_back("Able whispers, \"This is not just a camp. They have someone leading rituals here.\"");
    sceneryLines.push_back("The shaman drags its staff through the dirt, tracing strange symbols.");
    sceneryLines.push_back("Chants echoe through the forest as the air grows colder.");
    sceneryLines.push_back("The goblin shaman grins, its eyes glowing with cruel intelligence.");

    runEncounter(
        player,
        playerSkills,
        className,
        createGoblinShaman(),
        "THIRD ENCOUNTER: SHAMAN'S GROVE",
        "Deeper in the forest, you find a clearing marked with bones, grotesque symbols, and dying embers. A shaman steps from behind a twisted tree, lifting a crooked staff as the air begins to hum with arcane.",
        sceneryLines,
        "The shaman looks physically weaker than the hobgoblin, but the symbols around the clearing pulse with magic."
    );
}
template <typename PlayerType>
void GoblinChieftainEncounter(PlayerType& player, vector<Skill> playerSkills, string className) {
    vector<string> sceneryLines;

    sceneryLines.push_back("The goblin camp erupts into panic as the chieftain steps forward.");
    sceneryLines.push_back("Able pulls the carriage back and shouts, \"This one is different!\"");
    sceneryLines.push_back("The chieftain drags his cleaver through the dirt, carving a line between you and him.");
    sceneryLines.push_back("The lesser goblinsare riled up, chanting for blood.");
    sceneryLines.push_back("The chieftain raises his blade. It's stained silver gleams back at you, marking it's next victim.");
    sceneryLines.push_back("The chieftain snarls, refusing to let you leave his camp alive.");

    runEncounter(
        player,
        playerSkills,
        className,
        createGoblinChief(),
        "WORLD 1 BOSS: GOBLIN CHIEF",
        "At the heart of the goblin camp, crude tents surround a fire pit filled with bones and stolen goods. The goblins fall silent as their leader rises from a broken wooden throne. The Goblin Chieftain points his cleaver toward you and roars. This is the final battle of the forest road.",
        sceneryLines,
        "The chieftain is larger and calmer than the others. His armor is crude, but his stance shows experience. Defeating him may break the goblin camp completely."
    );
}

//Able's shop & update shop level after boss
template <typename PlayerType>
void ableShop(PlayerType& player, int shopLevel) {
    int choice;

    while (true) {
        slowPrintLine("\n\"Take whatever you need,\"", 15);

        cout << "\n===== ABLE'S SHOP =====\n";
        cout << "Gold: " << player.getGold() << "\n\n";

        cout << "1. Buy Health Potion - 10 gold\n";

        if (shopLevel >= 2) {
            cout << "2. Buy Greater Health Potion - 20 gold\n";
        }

        if (shopLevel >= 3) {
            cout << "3. Buy Titan's Blood - 25 gold\n";
            cout << "   Increases skill damage by 20% for the rest of battle.\n";

            cout << "4. Buy Cursed Beetle Larvae - 25 gold\n";
            cout << "   Reduces enemy damage by 20% for the rest of battle.\n";
        }

        if (shopLevel >= 4) {
            cout << "5. Buy Dancer's Talisman - 40 gold\n";
            cout << "   Restores 30 HP, increases your damage by 20%, and reduces enemy damage by 20% for the rest of battle.\n";
        }
        cout << "9. Leave Shop\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (player.spendGold(10)) {
                player.addItem("Health Potion");
                cout << "\nAble hands you a Health Potion.\n";
            }
            else {
                cout << "\nYou do not have enough gold.\n";
            }
        }
        else if (choice == 2 && shopLevel >= 2) {
            if (player.spendGold(20)) {
                player.addItem("Greater Health Potion");
                cout << "\nAble hands you a Greater Health Potion.\n";
            }
            else {
                cout << "\nYou do not have enough gold.\n";
            }
        }
        else if (choice == 3 && shopLevel >= 3) {
            if (player.spendGold(25)) {
                player.addItem("Titan's Blood");
                cout << "\nAble hands you a vial of Titan's Blood.\n";
            }
            else {
                cout << "\nYou do not have enough gold.\n";
            }
        }
        else if (choice == 4 && shopLevel >= 3) {
            if (player.spendGold(25)) {
                player.addItem("Cursed Beetle Larvae");
                cout << "\nAble hands you a sealed jar of Cursed Beetle Larvae.\n";
            }
            else {
                cout << "\nYou do not have enough gold.\n";
            }
        }
        else if (choice == 5 && shopLevel >= 4) {
            if (player.spendGold(40)) {
                player.addItem("Dancer's Talisman");
                cout << "\nAble hands you the Dancer's Talisman.\n";
            }
            else {
                cout << "\nYou do not have enough gold.\n";
            }
        }
        else if (choice == 9) {
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
void restCamp(PlayerType& player, string locationName, string sceneryText, string ableDialogue, string className, int shopLevel) {
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
            ableShop(player, shopLevel);
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


//World one!
template <typename PlayerType>
void worldOne(PlayerType& player, vector<Skill> playerSkills, string className, string playerName, string firstVictoryText) {
    cout << "\n===== WORLD 1: FOREST ROAD =====\n";
    slowPrintLine("Able guides the carriage deeper along the forest road.", 15);

    GoblinEncounter(player, playerSkills, className);

    if (player.getCurrentHP() <= 0) {
        return;
    }

    restCamp(
        player,
        "Forest Road",
        firstVictoryText,
        "\"You had me worried. You seem to be a seasoned veteran. The sun's setting. Let's set up camp.\"",
        className,
        1
    );

    slowPrintLine("\nYou wake up to the sun in your eyes and birds chirping.", 15);
    slowPrintLine("Able kneels beside a small fire, preparing a simple meal.", 15);
    slowPrintLine("\"" + playerName + ", glad to see your not dead. \"", 15);
    slowPrintLine("\"There's word of a goblin camp in the woods, and the guild pays well to clear it out.\"", 15);
    slowPrintLine("Seeing how much gold you have, you decide it would not be a bad idea to investigate.", 15);
    slowPrintLine("You also hope that fighting may sharpen your mind and reveal more about your past.", 15);

    HobgoblinEncounter(player, playerSkills, className);
    if (player.getCurrentHP() <= 0) {
        return;
    }
    restCamp(
        player,
        "Deeper Forest",
        "The hobgoblin falls, and the forest becomes still again. The signs of a larger camp are now impossible to ignore.",
        "\"That was no ordinary goblin. Something more sinister is waiting deeper in the woods.\"",
        className
        1
    );

    GoblinShamanEncounter(player, playerSkills, className);
    if (player.getCurrentHP() <= 0) {
        return;
    }
    restCamp(
        player,
        "Shaman's Grove",
        "The shaman collapses beside the dying embers. The strange symbols in the dirt fade as the forest releases a long, quiet breath.",
        "\"That magic was keeping something hidden. We're close.\"",
        className
        1
    );

    //World 1 boss
    GoblinChieftainEncounter(player, playerSkills, className);
    if (player.getCurrentHP() <= 0) {
        return;
    }
    restCamp(
        player,
        "Cleared Goblin Camp",
        "The Goblin Chief falls, and the remaining goblins scatter into the trees.",
        "\"You did it. The guild will pay well for this, but more importantly, you survived. Maybe your memories are starting to return.\"",
        className,
        2
    );
}
