#include <iostream>
#include <string>
#include "PlayerClasses.hpp"
#include "Monster.hpp"
#include "Skills.hpp"
#include "Encounters.hpp"
#include "TextHelp.hpp"
#include <cstdlib>
#include <ctime>
using namespace std;

string openingScene() {

    string playerName;

    slowPrintLine("\nYou jolt awake.", 40);
    slowPrintLine("The world rocks beneath you as wooden wheels grind against a dirt road.", 40);
    slowPrintLine("You are inside a moving carriage, but your memory feels broken and hazy.", 40);
    cout << endl;

    slowPrintLine("\"Adventurer, you're awake. I wasn't able to properly introduce myself last night.\"", 60);
    slowPrintLine("\"I'm Able. What's your name?\"", 40);
    cout << endl;

    cout << "Enter your name: ";
    cin >> playerName;
    cout << endl;

    slowPrintLine("\"It's " + playerName + ",\" you say.", 40);
    cout << endl;

    slowPrintLine("\"So, " + playerName + ", why are you traveling alone?\"", 40);
    slowPrintLine("\"It's been getting dangerous lately with frequent monster attacks.\"", 40);
    cout << endl;

    slowPrintLine("The carriage suddenly comes to a halt.", 40);
    slowPrintLine("You turn your head toward the road and see a group of goblins blocking the path.", 40);
    cout << endl;

    slowPrintLine("\"" + playerName + ", you know how to fight, right?\"", 40);
    cout << endl;

    slowPrintLine("Your memory is still clouded, but pieces of your past begin to return.", 40);
    slowPrintLine("You remember being one of four things:", 40);
    cout << endl;

    slowPrintLine("A legendary warrior who took down opponents and monsters said to be undefeatable.", 40);
    cout << endl;

    slowPrintLine("A great wizard whose magic was drawn from the Weave and blessed by the goddess Mystra.", 40);
    cout << endl;

    slowPrintLine("A miracle cleric whose healing power could cure deadly illnesses and restore the wounded.", 40);
    cout << endl;

    slowPrintLine("Or a shadow in the night, a rogue unmatched in stealth and feared across the land.", 40);
    cout << endl;

    slowPrintLine("The goblins draw their weapons.", 40);
    slowPrintLine("You must remember who you are.", 40);
    cout << endl;

    return playerName;

}
void printClassMenu(){

    cout << "Choose your class:\n\n";
    cout << "1. Warrior\n";
    cout << "   Highest HP and strength. Best for surviving long fights.\n\n";

    cout << "2. Wizard\n";
    cout << "   Highest intellect. Best for magic damage.\n\n";

    cout << "3. Cleric\n";
    cout << "   Balanced HP and intellect. Best for support and survival.\n\n";

    cout << "4. Rogue\n";
    cout << "   Strong physical damage. Best for quick attacks.\n\n";

    cout << "Enter choice: ";
    
};

//Failsafe if player makes a choice that is not 1 - 4 
int getClassChoice() {

    int choice;

    while (true) {
        printClassMenu();
        cin >> choice;
        if (choice >= 1 && choice <= 4) {
            return choice;
        }

        cout << "\n Please choose 1, 2, 3, or 4.\n\n";
    }

}

int main() {
   srand(time(0));
    //Player Choice
    string playerName;
    int choice;
    playerName = openingScene();
    choice = getClassChoice();

    //use player.gainXP(210); below class declaration to test at max level.
    if (choice == 1) {
        Warrior player;

        cout << "\n" << playerName << " remembers the path of the Warrior.\n";
        slowPrintLine("Prepare for battle!", 40);

        worldOne(
            player,
            getWarriorSkills(),
            "Warrior",
            playerName,
            "The goblins scatter in a frenzy after seeing their scout defeated. You stand triumphantly as sunlight cuts through the trees."
        );
        if (player.getCurrentHP() > 0) {
            worldTwo(player, getWarriorSkills(), "Warrior", playerName);
        }
    }
    

    else if (choice == 2) {
        Wizard player;

        cout << "\n" << playerName << " remembers the path of the Wizard.\n";
        slowPrintLine("Prepare for battle!", 40);

        worldOne(
            player,
            getWizardSkills(),
            "Wizard",
            playerName,
            "The goblin's body lies still on the road, singed by your arcane power. Faint sparks fade into the dirt."
        );
        if (player.getCurrentHP() > 0) {
            worldTwo(player, getWizardSkills(), "Wizard", playerName);
        }
    }
    else if (choice == 3) {
        Cleric player;

        cout << "\n" << playerName << " remembers the path of the Cleric.\n";
        slowPrintLine("Prepare for battle!", 40);

        worldOne(
            player,
            getClericSkills(),
            "Cleric",
            playerName,
            "The goblin falls into your arms. For a moment, you see its soul drift away as you gently close its eyes."
        );
        if (player.getCurrentHP() > 0) {
            worldTwo(player, getClericSkills(), "Cleric", playerName);
        }
    }
    else if (choice == 4) {
        Rogue player;

        cout << "\n" << playerName << " remembers the path of the Rogue.\n";
        slowPrintLine("Prepare for battle!", 40);

        worldOne(
            player,
            getRogueSkills(),
            "Rogue",
            playerName,
            "The goblin's body lies lifeless on the road. You let out a nervous chuckle, thankful you lived to see another day."
        );
        if (player.getCurrentHP() > 0) {
            worldTwo(player, getRogueSkills(), "Rogue", playerName);
        }
    }
    return 0;

}

