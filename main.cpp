#include <iostream>
#include <string>
#include "PlayerClasses.hpp"
#include "Monster.hpp"
#include "Skills.hpp"
#include "Encounters.hpp"
using namespace std;

string openingScene(){

    //Epic exposition scene
    string playerName;
    cout << "\nYou jolt awake.\n";
    cout << "The world rocks beneath you as wooden wheels grind against a dirt road.\n";
    cout << "You are inside a moving carriage, but your memory feels broken and hazy.\n\n"; 

    cout << "\"Adventurer, you're awake. I wasn't able to properly introduce myself last night.\"\n";
    cout << "\"I'm Able. What's your name?\"\n\n";

    cout << "Enter your name: ";
    cin >> playerName;

    cout << "\n\"It's " << playerName << ",\" you say.\n\n";

    cout << "\"So, " << playerName << ", why are you traveling alone?\"\n";
    cout << "\"It's been getting dangerous lately with frequent monster attacks.\"\n\n";

    cout << "The carriage suddenly comes to a halt.\n";
    cout << "You turn your head toward the road and see a goblin blocking the path.\n\n";
    cout << "\""<< playerName << ", you know how to fight, right?\"\n\n";

    cout << "Your memory is still clouded, but pieces of your past begin to return.\n";
    cout << "You remember being one of four things:\n\n";

    cout << "A legendary warrior who took down opponents and monsters said to be undefeatable.\n\n";
    cout << "A great wizard whose magic surpassed dragons and seemed to rewrite the world.\n\n";
    cout << "A miracle cleric whose healing power could cure deadly illnesses and restore the wounded.\n\n";
    cout << "Or a shadow in the night, a rogue unmatched in stealth and feared across the land.\n\n";
    cout << "The goblins draw their weapons.\n";
    cout << "You must remember who you are.\n\n";

    return playerName;
};
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
    Warrior warr1;
    Wizard wiz1;
    Cleric cler1;
    Rogue rog1;

    //Player Choice
    string playerName;
    int choice;
    playerName = openingScene();
    choice = getClassChoice();

    if (choice == 1) {
        Warrior player;
        cout << "\n" << playerName << " remembers the path of the Warrior.\n";
        cout << "Prepare for battle!\n";
        firstGoblinEncounter(player, getWarriorSkills(), "Warrior");
    }
    else if (choice == 2) {
        Wizard player;
        cout << "\n" << playerName << " remembers the path of the Wizard.\n";
        cout << "Prepare for battle!\n";
        firstGoblinEncounter(player, getWizardSkills(), "Wizard");
    }
    else if (choice == 3) {
        Cleric player;
        cout << "\n" << playerName << " remembers the path of the Cleric.\n";
        cout << "Prepare for battle!\n";
        firstGoblinEncounter(player, getClericSkills(), "Cleric");
    }
    else if (choice == 4) {
        Rogue player;
        cout << "\n" << playerName << " remembers the path of the Rogue.\n";
        cout << "Prepare for battle!\n";
        firstGoblinEncounter(player, getRogueSkills(), "Rogue");

    }


    

    return 0;

}
