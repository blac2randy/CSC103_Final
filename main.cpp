#include <iostream>
#include <string>
#include "PlayerClasses.hpp"
#include "Monster.hpp"
#include "Skills.hpp"
#include "Encounters.hpp"
#include "TextHelp.hpp"
using namespace std;

string openingScene() {

    string playerName;

    slowPrintLine("\nYou jolt awake.", 30);
    slowPrintLine("The world rocks beneath you as wooden wheels grind against a dirt road.", 25);
    slowPrintLine("You are inside a moving carriage, but your memory feels broken and hazy.", 25);
    cout << endl;

    slowPrintLine("\"Adventurer, you're awake. I wasn't able to properly introduce myself last night.\"", 25);
    slowPrintLine("\"I'm Able. What's your name?\"", 25);
    cout << endl;

    cout << "Enter your name: ";
    cin >> playerName;
    cout << endl;

    slowPrintLine("\"It's " + playerName + ",\" you say.", 25);
    cout << endl;

    slowPrintLine("\"So, " + playerName + ", why are you traveling alone?\"", 25);
    slowPrintLine("\"It's been getting dangerous lately with frequent monster attacks.\"", 25);
    cout << endl;

    slowPrintLine("The carriage suddenly comes to a halt.", 30);
    slowPrintLine("You turn your head toward the road and see a group of goblins blocking the path.", 25);
    cout << endl;

    slowPrintLine("\"" + playerName + ", you know how to fight, right?\"", 25);
    cout << endl;

    slowPrintLine("Your memory is still clouded, but pieces of your past begin to return.", 25);
    slowPrintLine("You remember being one of four things:", 25);
    cout << endl;

    slowPrintLine("A legendary warrior who took down opponents and monsters said to be undefeatable.", 25);
    cout << endl;

    slowPrintLine("A great wizard whose magic drawn from the weave called upon by their Goddess Mystra.", 25);
    cout << endl;

    slowPrintLine("A miracle cleric whose healing power could cure deadly illnesses and restore the wounded.", 25);
    cout << endl;

    slowPrintLine("Or a shadow in the night, a rogue unmatched in stealth and feared across the land.", 25);
    cout << endl;

    slowPrintLine("The goblins draw their weapons.", 30);
    slowPrintLine("You must remember who you are.", 35);
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
   
    //Player Choice
    string playerName;
    int choice;
    playerName = openingScene();
    choice = getClassChoice();

    if (choice == 1) {
        Warrior player;

        cout << "\n" << playerName << " remembers the path of the Warrior.\n";
        slowPrintLine("Prepare for battle!", 30);
        firstGoblinEncounter(player, getWarriorSkills(), "Warrior");
    }
    else if (choice == 2) {
        Wizard player;
        cout << "\n" << playerName << " remembers the path of the Wizard.\n";
        slowPrintLine("Prepare for battle!", 30);
        firstGoblinEncounter(player, getWizardSkills(), "Wizard");
    }
    else if (choice == 3) {
        Cleric player;
        cout << "\n" << playerName << " remembers the path of the Cleric.\n";
        slowPrintLine("Prepare for battle!", 30);
        firstGoblinEncounter(player, getClericSkills(), "Cleric");
    }
    else if (choice == 4) {
        Rogue player;
        cout << "\n" << playerName << " remembers the path of the Rogue.\n";
        slowPrintLine("Prepare for battle!", 30);
        firstGoblinEncounter(player, getRogueSkills(), "Rogue");

    }
    return 0;
}