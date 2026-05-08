#include <iostream>
#include "PlayerClasses.hpp"


int main() {
    Warrior warr1;
    Wizard wiz1;
    Cleric cler1;
    Rogue rog1;
    cout << "=== CLASS STAT TEST ===\n\n";

    cout << "Warrior\n";
    cout << "- Max HP: " << warr1.getMaxHP() << '\n';
    cout << "- Current HP: " << warr1.getCurrentHP() << '\n';
    cout << "- Strength: " << warr1.getStrength() << '\n';
    cout << "- Intellect: " << warr1.getIntellect() << "\n\n";

    cout << "Wizard\n";
    cout << "- Max HP: " << wiz1.getMaxHP() << '\n';
    cout << "- Current HP: " << wiz1.getCurrentHP() << '\n';
    cout << "- Strength: " << wiz1.getStrength() << '\n';
    cout << "- Intellect: " << wiz1.getIntellect() << "\n\n";

    cout << "Cleric\n";
    cout << "- Max HP: " << cler1.getMaxHP() << '\n';
    cout << "- Current HP: " << cler1.getCurrentHP() << '\n';
    cout << "- Strength: " << cler1.getStrength() << '\n';
    cout << "- Intellect: " << cler1.getIntellect() << "\n\n";

    cout << "Rogue\n";
    cout << "- Max HP: " << rog1.getMaxHP() << '\n';
    cout << "- Current HP: " << rog1.getCurrentHP() << '\n';
    cout << "- Strength: " << rog1.getStrength() << '\n';
    cout << "- Intellect: " << rog1.getIntellect() << "\n\n";

    return 0;

}