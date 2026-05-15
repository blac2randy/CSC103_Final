#pragma once
#include <iostream>
#include <string>
#include "PlayerClasses.hpp"
#include "Monster.hpp"
#include "Skills.hpp"
#include <string>
#include <vector>
#include "TextHelp.hpp" 
#include <cstdlib>
#include <ctime>
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
    cout << "Tarot Blessing: " << player.getTarotBlessing() << endl;

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
Monster createBogBlight() {
    return Monster(
        "Bog Blight",
        "A plant creature made of mud, roots, and rotting vines. It drags itself forward with wet claws.",
        30,
        5,
        2,
        30,
        10
    );
}

Monster createHexboundKnight() {
    return Monster(
        "Hexbound Knight",
        "A silent armored warrior covered in witch marks. Its rusted blade moves as if pulled by invisible strings.",
        36,
        6,
        2,
        35,
        15
    );
}

Monster createWillOWisp() {
    return Monster(
        "Will-o'-Wisp",
        "A floating ghost-light that flickers between the trees. Its glow feels warm, but something about it feels hungry.",
        28,
        2,
        7,
        40,
        18
    );
}

Monster createMireWitch() {
    return Monster(
        "Mire Witch",
        "An ancient witch draped in moss, feathers, and charms. Her smile widens as if she already knows your name.",
        60,
        4,
        9,
        60,
        25
    );
}
Monster createGraveboundSoldier() {
    return Monster(
        "Gravebound Soldier",
        "An undead soldier in cracked armor. Mud and gravewater drip from its shield as it marches forward.",
        42,
        7,
        2,
        45,
        18
    );
}

Monster createBoneCollector() {
    return Monster(
        "Bone Collector",
        "A corpse-like creature carrying a sack of bones. Its fingers are long, sharp, and eager.",
        46,
        6,
        4,
        50,
        20
    );
}

Monster createMourningWraith() {
    return Monster(
        "Mourning Wraith",
        "A ghostly figure wrapped in torn funeral cloth. Its voice sounds like several people crying at once.",
        40,
        3,
        9,
        55,
        22
    );
}

Monster createSealedRevenant() {
    return Monster(
        "Sealed Revenant",
        "A towering undead knight chained to a broken seal. Its armor bears the same symbol Able found with you.",
        75,
        9,
        6,
        75,
        40
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
template <typename PlayerType>
void BogBlightEncounter(PlayerType& player, vector<Skill> playerSkills, string className) {
    vector<string> sceneryLines;

    sceneryLines.push_back("Black water bubbles beside the path.");
    sceneryLines.push_back("Able pulls his cloak tighter and whispers, \"This place is wrong.\"");
    sceneryLines.push_back("Rotting vines twitch across the mud like living fingers.");
    sceneryLines.push_back("The trees lean inward, their branches twisting like claws.");
    sceneryLines.push_back("A wet dragging sound follows you through the fog.");

    runEncounter(
        player,
        playerSkills,
        className,
        createBogBlight(),
        "WORLD 2 - ENCOUNTER 1: THE ROTTEN PATH",
        "The road beyond the goblin camp sinks into a black marsh. The air smells of mud, rot, and ancient magic. As you step forward, a mass of roots and swamp water rises from the bog. Able backs away from the creature. \"It dosen't possess a mind of it's own.\"",
        sceneryLines,
        "The creature is slow, its body constantly keeps pulling itself back together with mud and roots."
    );
}
template <typename PlayerType>
void HexboundKnightEncounter(PlayerType& player, vector<Skill> playerSkills, string className) {
    vector<string> sceneryLines;

    sceneryLines.push_back("A rusted helmet hangs from a branch, swaying without wind.");
    sceneryLines.push_back("Able points toward the armor and says, \"That crest belongs to a dead order.\"");
    sceneryLines.push_back("The knight's sword scrapes across stone buried beneath the mud.");
    sceneryLines.push_back("Hex marks glow faintly across the armor.");
    sceneryLines.push_back("The knight does not breathe. It only waits. The wind howls");

    runEncounter(
        player,
        playerSkills,
        className,
        createHexboundKnight(),
        "WORLD 2 - ENCOUNTER 2: THE HEXBOUND KNIGHT",
        "Deeper in the Witchwood, you find a ruined shrine half-swallowed by moss. Kneeling before it is an armored knight. For a moment, it looks dead. Then violet symbols burn across its armor, and it rises with its blade drawn. Able whispers, \"A curse is wearing that body like a puppet.\"",
        sceneryLines,
        "The knight fights with discipline, but its movements are unnatural. The glowing marks may be the source of the curse."
    );
}
template <typename PlayerType>
void WillOWispEncounter(PlayerType& player, vector<Skill> playerSkills, string className) {
    vector<string> sceneryLines;

    sceneryLines.push_back("Pale lights drift between the trees, vanishing when you look directly at them.");
    sceneryLines.push_back("Able warns, \"Do not follow the lights. They want you lost.\"");
    sceneryLines.push_back("The fog thickens, you barely lose sight of the carriage.");
    sceneryLines.push_back("A child's laugh echoes from somewhere in the marsh.");
    sceneryLines.push_back("The ghost-light pulses brighter, feeding on your confusion.");

    runEncounter(
        player,
        playerSkills,
        className,
        createWillOWisp(),
        "WORLD 2 - ENCOUNTER 3: THE LIGHT",
        "As night falls, a pale blue light appears ahead of you. It flickers like a lantern, then splits into several ghostly flames. One drifts close, Able grabs your shoulder. \"That is no lantern. It is bait.\"",
        sceneryLines,
        "The Will-o'-Wisp is fragile but magical. Its glow seems to pull at your thoughts, almost like it is trying to steal memories."
    );
}
template <typename PlayerType>
void MireWitchEncounter(PlayerType& player, vector<Skill> playerSkills, string className) {
    vector<string> sceneryLines;

    sceneryLines.push_back("The witch's hut creaks on crooked wooden legs.");
    sceneryLines.push_back("Bone charms rattle above the doorway.");
    sceneryLines.push_back("Able's voice shakes. \"She knows we're here. She has known for a while.\"");
    sceneryLines.push_back("The swamp water rises around your feet as the witch laughs.");
    sceneryLines.push_back("The witch whispers your name, though you never told her.");
    sceneryLines.push_back("For a moment, a piece of your memory flashes behind your eyes. You have forgotten it ");

    runEncounter(
        player,
        playerSkills,
        className,
        createMireWitch(),
        "WORLD 2 BOSS: THE WITCH",
        "At the heart of the Witchwood stands a crooked hut surrounded by candles, skulls, and black water. An old woman steps from the doorway, but her shadow bends in the wrong direction. She smiles at you as if greeting an old friend. \"Lost little hero,\" she says. \"Still trying to remember what you buried?\" Able goes pale. \"That is the witch. Do not listen to her.\"",
        sceneryLines,
        "The Mire Witch is physically weak, but her magic is far stronger. Her words seem aimed at your forgotten past."
    );
}
template <typename PlayerType>
void GraveboundSoldierEncounter(PlayerType& player, vector<Skill> playerSkills, string className) {
    vector<string> sceneryLines;

    sceneryLines.push_back("Cold mist rolls over cracked stone steps.");
    sceneryLines.push_back("Able holds up a lantern, but its flame burns blue.");
    sceneryLines.push_back("The soldier's shield scrapes against the catacomb wall.");
    sceneryLines.push_back("Water bleeds from the walls of the chamber.");
    sceneryLines.push_back("The undead soldier marches without hesitation.");

    runEncounter(
        player,
        playerSkills,
        className,
        createGraveboundSoldier(),
        "WORLD 3 - ENCOUNTER 1: CATACOMB GATE",
        "Beyond the Witchwood, the road sinks into an ancient burial ground. Broken stone doors rise from the mud, marked with the same symbol from Able's broken seal. As you approach, an undead soldier pulls itself from the flooded earth and raises its shield.",
        sceneryLines,
        "The soldier fights like it remembers orders from a war long forgotten."
    );
}
template <typename PlayerType>
void BoneCollectorEncounter(PlayerType& player, vector<Skill> playerSkills, string className) {
    vector<string> sceneryLines;

    sceneryLines.push_back("Bones rattle somewhere in the darkness.");
    sceneryLines.push_back("Able whispers, \"Do not step on anything that looks like a hand.\"");
    sceneryLines.push_back("The creature drags its sack behind it, leaving white scratches on the stone.");
    sceneryLines.push_back("Skulls in the walls shift slighty as you pass.");
    sceneryLines.push_back("The Bone Collector clicks its teeth as if counting pieces.");

    runEncounter(
        player,
        playerSkills,
        className,
        createBoneCollector(),
        "WORLD 3 - ENCOUNTER 2: CATACOMBS",
        "Inside the catacombs, the walls are packed with old bones and rusted weapons. A corpse-like creature bends over a pile of remains, selecting bones as if choosing tools. It turns toward you and opens its sack.",
        sceneryLines,
        "The Bone Collector looks fragile, but its long arms give it dangerous reach. It seems eager to add your bones to its collection."
    );
}
template <typename PlayerType>
void MourningWraithEncounter(PlayerType& player, vector<Skill> playerSkills, string className) {
    vector<string> sceneryLines;

    sceneryLines.push_back("A sobs echo through the flooded chamber.");
    sceneryLines.push_back("Able lowers his lantern and says, \"That voice is not alive.\"");
    sceneryLines.push_back("The air grows colder whenever the wraith looks at you.");
    sceneryLines.push_back("Old names are carved into the walls, but one has been scratched away.");
    sceneryLines.push_back("The wraith reaches toward you as if it recognizes your face.");

    runEncounter(
        player,
        playerSkills,
        className,
        createMourningWraith(),
        "WORLD 3 - ENCOUNTER 3: THE CRYPT",
        "At the center of the catacombs, you enter a flooded crypt filled with broken statues. A ghostly figure drifts above the water, weeping into her hands. She looks up, she whispers a name you almost recognize.",
        sceneryLines,
        "The wraith is drawn to you as if your past is tied to this crypt."
    );
}
template <typename PlayerType>
void SealedRevenantEncounter(PlayerType& player, vector<Skill> playerSkills, string className) {
    vector<string> sceneryLines;

    sceneryLines.push_back("The broken seal pulses with dull red light.");
    sceneryLines.push_back("Able steps back, staring at the symbol on the floor.");
    sceneryLines.push_back("Chains drag across stone as the revenant raises its blade.");
    sceneryLines.push_back("The catacombs tremble as forgotten magic wakes beneath your feet.");
    sceneryLines.push_back("The revenant speaks in a hollow voice: \"Sealbreaker.\"");
    sceneryLines.push_back("A memory flashes through your mind: your hand on this same seal long ago.");

    runEncounter(
        player,
        playerSkills,
        className,
        createSealedRevenant(),
        "WORLD 3 BOSS: THE SEALED REVENANT",
        "Deep beneath the catacombs, you find a circular chamber built around a broken magical seal. Chains hang from the ceiling, all leading to a kneeling undead noble. As you step closer, the seal reacts to you. The knight rises and speaks one word: \"Sealbreaker.\" Able looks at you, shaken. \"That symbol... it was on the thing I found with you.\" The revenant points its blade at your chest. \"You were not sealed away to protect you. You were sealed away to protect everyone else.\"",
        sceneryLines,
        "The revenant is not just guarding the chamber. It recognizes you. Every word it speaks pulls a violent force from deep inside your mind."
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

// Able Dialogue
void talkToAble(int dialogueLevel) {
    int choice;

    while (true) {
        cout << "\n===== TALK TO ABLE =====\n";
        cout << "1. Ask about Able\n";
        cout << "2. Ask about the road ahead\n";

        if (dialogueLevel >= 2) {
            cout << "3. Ask about your lost memories\n";
        }

        if (dialogueLevel >= 3) {
            cout << "4. Ask about the witch's words\n";
        }

        if (dialogueLevel >= 4) {
            cout << "5. Ask what Able is hiding\n";
        }

        cout << "9. Leave conversation\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            slowPrintLine("\nYou ask Able why he travels these roads.", 15);
            slowPrintLine("\"I used to be a merchant for safer towns,\" Able says.", 15);
            slowPrintLine("\"When I found you you seemed to be either dead or asleep so I thought I'd get you to a church or doctor.\"", 15);
        }
        else if (choice == 2) {
            slowPrintLine("\nYou ask Able about the road ahead.", 15);
            slowPrintLine("\"Roads tell stories if you pay attention,\" Able says.", 15);
            slowPrintLine("\"Broken branches, missing travelers, frightened animals... they all point to trouble before trouble shows itself.\"", 15);
        }
        else if (choice == 3 && dialogueLevel >= 2) {
            slowPrintLine("\nYou ask Able if he knows anything about your missing memories.", 15);
            slowPrintLine("Able goes quiet for a moment.", 15);
            slowPrintLine("\"I do not know who you were,\" he says. \"But I know how you fight. That kind of skill does not come from nowhere.\"", 15);
        }
        else if (choice == 4 && dialogueLevel >= 3) {
            slowPrintLine("\nYou ask Able about what the witch said.", 15);
            slowPrintLine("\"She wanted to shake you,\" Able says. \"Witches do not always lie. But for all we know she could just be crazy.\"", 15);
            slowPrintLine("\"If she knew your name, then your past is tied to more than to just waking randomly.\"", 15);
        }
        else if (choice == 5 && dialogueLevel >= 4) {
            slowPrintLine("\nYou ask Able what he is not telling you.", 15);
            slowPrintLine("Able looks away from the fire.", 15);
            slowPrintLine("\"When I found you, you were carrying something. A broken seal. I did not tell you because I was not sure what it meant.\"", 15);
        }
        else if (choice == 9) {
            slowPrintLine("\nAble nods and returns to checking the supplies.", 15);
            return;
        }
        else {
            cout << "\nInvalid choice.\n";
        }
    }
}
//Tarot Game using rand()
template <typename PlayerType>
void tarotReading(PlayerType& player) {
    int card = rand() % 6 + 1;

    cout << "\n===== TAROT READING =====\n";
    slowPrintLine("Able pulls a small deck of cards from his coat.", 15);
    slowPrintLine("\"These are not for fortune,\" he says. \"They show pressure. Possibility. Consequence.\"", 15);
    slowPrintLine("You draw one card from the deck...", 20);

    if (card == 1) {
        slowPrintLine("\nYou drew: THE SUN", 20);
        slowPrintLine("Warm light spreads through your chest.", 15);

        player.applyTarotBlessing("The Sun: +5 Max HP", 5, 0, 0);

        cout << "Permanent Effect: Max HP increased by 5.\n";
    }
    else if (card == 2) {
        slowPrintLine("\nYou drew: THE TOWER", 20);
        slowPrintLine("For a moment, you feel everything inside you break and rebuild.", 15);

        player.applyTarotBlessing("The Tower: +4 STR, took 5 damage", 0, 4, 0);
        player.takeDamage(5);

        cout << "Permanent Effect: Strength increased by 4.\n";
        cout << "Drawback: You took 5 damage.\n";
    }
    else if (card == 3) {
        slowPrintLine("\nYou drew: THE MOON", 20);
        slowPrintLine("A quiet voice whispers forgotten truths behind your eyes.", 15);

        player.applyTarotBlessing("The Moon: +4 INT", 0, 0, 4);

        cout << "Permanent Effect: Intellect increased by 4.\n";
    }
    else if (card == 4) {
        slowPrintLine("\nYou drew: THE HANGED MAN", 20);
        slowPrintLine("Your body feels heavy, but your mind sharpens through sacrifice.", 15);

        player.applyTarotBlessing("The Hanged Man: +3 INT, took 3 damage", 0, 0, 3);
        player.takeDamage(3);

        cout << "Permanent Effect: Intellect increased by 3.\n";
        cout << "Drawback: You took 3 damage.\n";
    }
    else if (card == 5) {
        slowPrintLine("\nYou drew: STRENGTH", 20);
        slowPrintLine("Your grip tightens. Your fear becomes fuel.", 15);

        player.applyTarotBlessing("Strength: +3 STR", 0, 3, 0);

        cout << "Permanent Effect: Strength increased by 3.\n";
    }
    else if (card == 6) {
        slowPrintLine("\nYou drew: DEATH", 20);
        slowPrintLine("The card does not mean the end. It means transformation.", 15);

        player.applyTarotBlessing("Death: +3 Max HP, +1 STR, +1 INT, took 4 damage", 3, 1, 1);
        player.takeDamage(4);

        cout << "Permanent Effect: Max HP increased by 3, Strength increased by 1, Intellect increased by 1.\n";
        cout << "Drawback: You took 4 damage.\n";
    }

    cout << "Current HP: " << player.getCurrentHP() << "/" << player.getMaxHP() << endl;
}
//Resting 
template <typename PlayerType>
void restCamp(PlayerType& player, string locationName, string sceneryText,
    string ableDialogue, string className, int shopLevel, int dialogueLevel) {
    int choice;
    bool tarotUsed = false;

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
        cout << "7. Draw a Tarot Card\n";
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
            talkToAble(dialogueLevel);
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
        else if (choice == 7) {
            if (tarotUsed) {
                cout << "\nAble shakes his head. \"One reading per rest. More would displease outer Gods.\"\n";
            }
            else {
                tarotReading(player);
                tarotUsed = true;
            }
        }
        else {
            cout << "\nInvalid choice. Please choose 1-7.\n";
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
        1,
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
        className,
        1,
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
        className,
        1,
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
        2,
        2
    );
    slowPrintLine("\nWith the goblin camp broken, the road ahead finally opens.", 40);
    slowPrintLine("Able secures the supplies and speaks to you.", 40);
    slowPrintLine("\"No idea who you were before but I'm lucky to have you on my side, let's get moving.\"", 40);
    slowPrintLine("\n===== WORLD 1 COMPLETE =====", 40);
}

template <typename PlayerType>
void worldTwo(PlayerType& player, vector<Skill> playerSkills, string className, string playerName) {
    cout << "\n===== WORLD 2: THE WITCHWOOD BOG =====\n";
    slowPrintLine("After clearing the goblin camp, Able leads the carriage toward a road swallowed by fog.", 15);
    slowPrintLine("The trees grow twisted, the air turns damp, and the sunlight fades behind gray mist.", 15);
    slowPrintLine("Able lowers his voice. \"Travelers say a witch lives in this bog. Most say it as a warning.\"", 15);

    BogBlightEncounter(player, playerSkills, className);

    if (player.getCurrentHP() <= 0) {
        return;
    }

    restCamp(
        player,
        "Rotten Path",
        "The Bog Blight sinks back into the mud, leaving only broken roots and black water behind.",
        "\"The swamp itself is fighting us. Whatever lives here has power over the land.\"",
        className,
        2,
        2
    );

    HexboundKnightEncounter(player, playerSkills, className);

    if (player.getCurrentHP() <= 0) {
        return;
    }

    restCamp(
        player,
        "Ruined Shrine",
        "The Hexbound Knight collapses, The hex marks fade from the rusted metal.",
        "\"That knight may have been guarding this place for years. Or trapped here. Hard to tell which is worse.\"",
        className,
        2,
        2
    );

    WillOWispEncounter(player, playerSkills, className);

    if (player.getCurrentHP() <= 0) {
        return;
    }

    restCamp(
        player,
        "Foglit Marsh",
        "The Will-o'-Wisp bursts into pale sparks, and the fog thins just enough to reveal a crooked hut in the distance.",
        "\"There. That hut. I think we found the heart of the curse.\"",
        className,
        2,
        2
    );

    MireWitchEncounter(player, playerSkills, className);

    if (player.getCurrentHP() <= 0) {
        return;
    }

    restCamp(
        player,
        "Witch's Hut",
        "The Mire Witch vanishes into black smoke, leaving behind bone charms, strange herbs, and a cracked mirror.",
        "\"She knew something about you. I do not think this journey is only about monsters anymore. I found better supplies in her hut. Take a look when you're ready.\"",
        className,
        3,
        3
    );

    slowPrintLine("\n===== WORLD 2 COMPLETE =====", 15);
    slowPrintLine("As the witch's magic fades, the road beyond the bog begins to reveal itself.", 15);
}
void finalChoice(string className) {
    int choice;

    cout << "\n===== FINAL CHOICE =====\n";
    slowPrintLine("The Urge wakes inside you.", 20);
    slowPrintLine("It does not speak with words.", 20);
    slowPrintLine("It speaks with hunger.", 20);

    cout << "\n1. Resist it\n";
    cout << "2. Embrace it\n";
    cout << "Enter choice: ";
    cin >> choice;

    if (choice == 1) {
        slowPrintLine("\nYou clench your fists and force the hunger back.", 20);

        if (className == "Warrior") {
            slowPrintLine("Your hands shake around an invisible weapon, but you refuse to swing.", 20);
            slowPrintLine("Strength was never just the power to destroy. It was the power to stop yourself.", 20);
        }
        else if (className == "Wizard") {
            slowPrintLine("Arcane power flickers around your fingers, wild and hungry.", 20);
            slowPrintLine("You bind it with sheer will, choosing thought over instinct.", 20);
        }
        else if (className == "Cleric") {
            slowPrintLine("A quiet prayer rises in your chest, not to erase what you are, but to guide you.", 20);
            slowPrintLine("Your faith holds true.", 20);
        }
        else if (className == "Rogue") {
            slowPrintLine("Every shadow around you seems to offer an easy escape into violence.", 20);
            slowPrintLine("You step into the light instead.", 20);
        }

        slowPrintLine("\nYour past may be stained, but your future is still unwritten.", 20);
        slowPrintLine("Able nods slowly.", 20);
        slowPrintLine("\"Then we keep moving,\" he says. \"One good choice at a time.\"", 20);
        slowPrintLine("\nENDING: THE URGE RESISTED", 25);
    }
    else if (choice == 2) {
        slowPrintLine("\nYou stop fighting the hunger.", 20);
        slowPrintLine("The fear, the guilt, the confusion... all of it fades beneath something sinister.", 20);

        if (className == "Warrior") {
            slowPrintLine("Your old strength returns like a war drum in your blood.", 20);
            slowPrintLine("Able sees the change in your stance and reaches for the reins.", 20);
        }
        else if (className == "Wizard") {
            slowPrintLine("The Weave bends around you, not like a gift, but like something afraid.", 20);
            slowPrintLine("Able whispers your name, but the sound feels distant.", 20);
        }
        else if (className == "Cleric") {
            slowPrintLine("The prayer in your chest twists into silence.", 20);
            slowPrintLine("Able steps back, realizing the light in your eyes is gone.", 20);
        }
        else if (className == "Rogue") {
            slowPrintLine("The shadows welcome you like an old friend.", 20);
            slowPrintLine("Able notices too late that you have already moved.", 20);
        }

        slowPrintLine("\nAble takes one step back.", 20);
        slowPrintLine("\"No,\" he says softly. \"That is not you.\"", 20);
        slowPrintLine("But the Urge answers before you can.", 20);
        slowPrintLine("When the carriage moves again, Able is no longer beside you.", 20);
        slowPrintLine("Only silence remains where your friend once stood.", 20);

        slowPrintLine("\nENDING: THE URGE AWAKENED", 25);
    }
    else {
        slowPrintLine("\nYou hesitate, unable to choose.", 20);
        slowPrintLine("Able watches you carefully, unsure whether to comfort you or fear you.", 20);
        slowPrintLine("The darkness waits patiently.", 20);
        slowPrintLine("\nENDING: UNDECIDED", 25);
    }
}
template <typename PlayerType>
void worldThree(PlayerType& player, vector<Skill> playerSkills, string className, string playerName) {
    cout << "\n===== WORLD 3: CATACOMBS OF TARTAUS =====\n";
    slowPrintLine("With the Witchwood behind you, the road sinks into low marshland and broken stone.", 15);
    slowPrintLine("Ahead, ancient doors rise from the mud like the entrance to a forgotten tomb.", 15);
    slowPrintLine("Able stops the carriage and pulls something from his coat: a broken seal marked with a strange symbol.", 15);
    slowPrintLine("\"I found this on you when I picked you up,\" he says. \"I think it belongs here.\"", 15);

    GraveboundSoldierEncounter(player, playerSkills, className);

    if (player.getCurrentHP() <= 0) {
        return;
    }

    restCamp(
        player,
        "Catacomb Gate",
        "The Gravebound Soldier falls apart, its armor sinking back into the mud. The ancient gate waits in silence.",
        "\"That thing was guarding the entrance. I do not think we are trespassing by accident anymore.\"",
        className,
        3,
        3
    );

    BoneCollectorEncounter(player, playerSkills, className);

    if (player.getCurrentHP() <= 0) {
        return;
    }

    restCamp(
        player,
        "Hall of Egress",
        "The Bone Collector collapses, spilling old bones across the stone floor. For a moment, the walls seem to sigh.",
        "\"This place has been feeding on the dead for a long time. Stay close to the lantern.\"",
        className,
        3,
        3
    );

    MourningWraithEncounter(player, playerSkills, className);

    if (player.getCurrentHP() <= 0) {
        return;
    }

    restCamp(
        player,
        "Nameless Crypt",
        "The Mourning Wraith fades into mist. The scratched-away name on the wall still pulls at your mind.",
        "\"She knew you. Or she thought she did. Either way, we are getting close to something you forgot.\"",
        className,
        3,
        3
    );

    SealedRevenantEncounter(player, playerSkills, className);

    if (player.getCurrentHP() <= 0) {
        return;
    }

    restCamp(
        player,
        "Broken Seal Chamber",
        "The Sealed Revenant falls to one knee before turning to ash. The broken seal glows once, then cracks apart completely. For a moment, your reflection appears in the dark stone floor, but it smiles before you do.",
        "\"I should have told you sooner,\" Able says. \"When I found you, that seal was clenched in your hand. I thought it was protecting you. Now I think it was holding something inside you.\"",
        className,
        4,
        4
    );

    slowPrintLine("\nA memory returns.", 15);
    slowPrintLine("Not a peaceful one.", 15);
    slowPrintLine("You see your hands covered in blood that is not yours.", 15);
    slowPrintLine("You hear people begging you to stop.", 15);
    slowPrintLine("And beneath it all, you feel something inside you smiling.", 15);
    slowPrintLine("\nThe name comes back like a curse:", 20);
    slowPrintLine("The Bloodbound Urge.", 30);

    slowPrintLine("\nAble stares at you carefully.", 15);
    slowPrintLine("\"Whatever you are,\" he says, \"you still get to choose what you do next.\"", 15);

    slowPrintLine("\n===== WORLD 3 COMPLETE =====", 15);

   finalChoice(className);
}