#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "hp.hpp"
#include "statsblock.hpp"
using namespace std;


// =============================
// Warrior Class
// Highest HP and strength
// =============================
class Warrior : public hp, public StatBlock {
private:
    int level;
    int xp;
    int xpToLevel;
    int maxLevel;
    vector<string> inventory;
    int gold;

    string tarotBlessing;
    int tarotHPBonus;
    int tarotSTRBonus;
    int tarotINTBonus;
public:
    static const hptype HPGROWTH = (hptype)17u;
    static const stattype BASESTR = (stattype)3u;
    static const stattype BASEINT = (stattype)1u;

    void setTarotBlessing(string blessingName) {
    tarotBlessing = blessingName;
    }
    string getTarotBlessing() {
        return tarotBlessing;
    }

    Warrior() : hp(HPGROWTH, HPGROWTH), StatBlock(BASESTR, BASEINT) {
        level = 1;
        xp = 0;
        xpToLevel = 30;
        maxLevel = 8;
        gold = 0;

        tarotBlessing = "None";
        tarotHPBonus = 0;
        tarotSTRBonus = 0;
        tarotINTBonus = 0;
        inventory.push_back("Health Potion");
        }

    void removeTarotEffects() {
        if (tarotHPBonus > 0) {
            setMaxHp(getMaxHP() - tarotHPBonus);
        }

        if (tarotSTRBonus > 0) {
            decreaseStrength(tarotSTRBonus);
        }

        if (tarotINTBonus > 0) {
            decreaseIntellect(tarotINTBonus);
        }

        tarotBlessing = "None";
        tarotHPBonus = 0;
        tarotSTRBonus = 0;
        tarotINTBonus = 0;
    }

    void applyTarotBlessing(string blessingName, int hpBonus, int strBonus, int intBonus) {
        removeTarotEffects();

        tarotBlessing = blessingName;
        tarotHPBonus = hpBonus;
        tarotSTRBonus = strBonus;
        tarotINTBonus = intBonus;

        if (tarotHPBonus > 0) {
            increaseMaxHP(tarotHPBonus);
            heal(tarotHPBonus);
        }

        if (tarotSTRBonus > 0) {
            increaseStrength(tarotSTRBonus);
        }

        if (tarotINTBonus > 0) {
            increaseIntellect(tarotINTBonus);
        }
    }
    int getLevel() {
        return level;
    }

    int getXP() {
        return xp;
    }
       void gainXP(int amount) {
        xp += amount;

        while (xp >= xpToLevel && level < maxLevel) {
            xp -= xpToLevel;
            levelUp();
        }
        if (level >= maxLevel) {
        xp = 0;

    }
        
    }
    void levelUp() {
        level++;
        increaseMaxHP(8);
        increaseStrength(2);
    }
    int getGold() {
    return gold;
}

void gainGold(int amount) {
    gold += amount;
}

bool spendGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    }

    return false;
}

void addItem(string itemName) {
    inventory.push_back(itemName);
}

int getInventorySize() {
    return inventory.size();
}

string getItem(int index) {
    if (index >= 0 && index < static_cast<int>(inventory.size())) {
        return inventory[index];
    }

    return "Invalid Item";
}

//Remove Items with specific effects
void removeItem(int index) {
    if (index >= 0 && index < static_cast<int>(inventory.size())) {
        inventory.erase(inventory.begin() + index);
    }
}

void showInventory() {
        cout << "\n===== INVENTORY =====\n";
        cout << "Gold: " << gold << endl;

        if (inventory.size() == 0) {
            cout << "Your inventory is empty.\n";
        }
        else {
            for (int i = 0; i < inventory.size(); i++) {
                cout << i + 1 << ". " << inventory[i] << endl;
            }
        }
    }

    bool useItem(int itemChoice) {
        int index = itemChoice - 1;

        if (index < 0 || index >= static_cast<int>(inventory.size())) {
            cout << "Invalid item choice.\n";
            return false;
        }

        string item = inventory[index];

        if (item == "Health Potion") {
            heal(10);
            cout << "You used a Health Potion and restored 10 HP.\n";

            removeItem(index);
            return true;
        }
        else if (item == "Greater Health Potion") {
            heal(25);
            cout << "You used a Greater Health Potion and restored 25 HP.\n";

            removeItem(index);
            return true;
        }

        cout << item << " can only be used during battle.\n";
        return false;
    }
};

// =============================
// Wizard Class
// Highest intellect / magic
// =============================
class Wizard : public hp, public StatBlock {
private:
    int level;
    int xp;
    int xpToLevel;
    int maxLevel;
    vector<string> inventory;
    int gold;

    string tarotBlessing;
    int tarotHPBonus;
    int tarotSTRBonus;
    int tarotINTBonus;

public:
    static const hptype HPGROWTH = (hptype)9u;
    static const stattype BASESTR = (stattype)1u;
    static const stattype BASEINT = (stattype)4u;

    void setTarotBlessing(string blessingName) {
    tarotBlessing = blessingName;
    }
    string getTarotBlessing() {
        return tarotBlessing;
    }

    Wizard() : hp(HPGROWTH, HPGROWTH), StatBlock(BASESTR, BASEINT) {
        level = 1;
        xp = 0;
        xpToLevel = 30;
        maxLevel = 8;
        gold = 0;

        tarotBlessing = "None";
        tarotHPBonus = 0;
        tarotSTRBonus = 0;
        tarotINTBonus = 0;
        inventory.push_back("Health Potion");
    }

    void removeTarotEffects() {
        if (tarotHPBonus > 0) {
            setMaxHp(getMaxHP() - tarotHPBonus);
        }

        if (tarotSTRBonus > 0) {
            decreaseStrength(tarotSTRBonus);
        }

        if (tarotINTBonus > 0) {
            decreaseIntellect(tarotINTBonus);
        }

        tarotBlessing = "None";
        tarotHPBonus = 0;
        tarotSTRBonus = 0;
        tarotINTBonus = 0;
    }

    void applyTarotBlessing(string blessingName, int hpBonus, int strBonus, int intBonus) {
        removeTarotEffects();

        tarotBlessing = blessingName;
        tarotHPBonus = hpBonus;
        tarotSTRBonus = strBonus;
        tarotINTBonus = intBonus;

        if (tarotHPBonus > 0) {
            increaseMaxHP(tarotHPBonus);
            heal(tarotHPBonus);
        }

        if (tarotSTRBonus > 0) {
            increaseStrength(tarotSTRBonus);
        }

        if (tarotINTBonus > 0) {
            increaseIntellect(tarotINTBonus);
        }
    }
    int getLevel() {
        return level;
    }

    int getXP() {
        return xp;
    }
       void gainXP(int amount) {
        xp += amount;

        while (xp >= xpToLevel && level < maxLevel) {
            xp -= xpToLevel;
            levelUp();
        }
        if (level >= maxLevel) {
        xp = 0;

    }
        
    }
    void levelUp() {
        level++;
        increaseMaxHP(4);
        increaseIntellect(2);
    }
    int getGold() {
    return gold;
}

void gainGold(int amount) {
    gold += amount;
}

bool spendGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    }

    return false;
}

void addItem(string itemName) {
    inventory.push_back(itemName);
}

int getInventorySize() {
    return inventory.size();
}

string getItem(int index) {
    if (index >= 0 && index < static_cast<int>(inventory.size())) {
        return inventory[index];
    }

    return "Invalid Item";
}
//Remove Items with specific effects
void removeItem(int index) {
    if (index >= 0 && index < static_cast<int>(inventory.size())) {
        inventory.erase(inventory.begin() + index);
    }
}

    void showInventory() {
        cout << "\n===== INVENTORY =====\n";
        cout << "Gold: " << gold << endl;

        if (inventory.size() == 0) {
            cout << "Your inventory is empty.\n";
        }
        else {
            for (int i = 0; i < inventory.size(); i++) {
                cout << i + 1 << ". " << inventory[i] << endl;
            }
        }
    }

    bool useItem(int itemChoice) {
        int index = itemChoice - 1;

        if (index < 0 || index >= static_cast<int>(inventory.size())) {
            cout << "Invalid item choice.\n";
            return false;
        }

        string item = inventory[index];

        if (item == "Health Potion") {
            heal(10);
            cout << "You used a Health Potion and restored 10 HP.\n";

            removeItem(index);
            return true;
        }
        else if (item == "Greater Health Potion") {
            heal(25);
            cout << "You used a Greater Health Potion and restored 25 HP.\n";

            removeItem(index);
            return true;
        }

        cout << item << " can only be used during battle.\n";
        return false;
    }
};

// =============================
// Cleric Class
// Balanced HP and intellect
// =============================
class Cleric : public hp, public StatBlock {
private:
    int level;
    int xp;
    int xpToLevel;
    int maxLevel;
    vector<string> inventory;
    int gold;

    string tarotBlessing;
    int tarotHPBonus;
    int tarotSTRBonus;
    int tarotINTBonus;

public:
    static const hptype HPGROWTH = (hptype)13u;
    static const stattype BASESTR = (stattype)2u;
    static const stattype BASEINT = (stattype)3u;
    
    void setTarotBlessing(string blessingName) {
    tarotBlessing = blessingName;
    }
    string getTarotBlessing() {
        return tarotBlessing;
    }

    Cleric() : hp(HPGROWTH, HPGROWTH), StatBlock(BASESTR, BASEINT) {
        level = 1;
        xp = 0;
        xpToLevel = 30;
        maxLevel = 8;
        gold = 0;

        tarotBlessing = "None";
        tarotHPBonus = 0;
        tarotSTRBonus = 0;
        tarotINTBonus = 0;
        inventory.push_back("Health Potion");
    }

    void removeTarotEffects() {
        if (tarotHPBonus > 0) {
            setMaxHp(getMaxHP() - tarotHPBonus);
        }

        if (tarotSTRBonus > 0) {
            decreaseStrength(tarotSTRBonus);
        }

        if (tarotINTBonus > 0) {
            decreaseIntellect(tarotINTBonus);
        }

        tarotBlessing = "None";
        tarotHPBonus = 0;
        tarotSTRBonus = 0;
        tarotINTBonus = 0;
    }

    void applyTarotBlessing(string blessingName, int hpBonus, int strBonus, int intBonus) {
        removeTarotEffects();

        tarotBlessing = blessingName;
        tarotHPBonus = hpBonus;
        tarotSTRBonus = strBonus;
        tarotINTBonus = intBonus;

        if (tarotHPBonus > 0) {
            increaseMaxHP(tarotHPBonus);
            heal(tarotHPBonus);
        }

        if (tarotSTRBonus > 0) {
            increaseStrength(tarotSTRBonus);
        }

        if (tarotINTBonus > 0) {
            increaseIntellect(tarotINTBonus);
        }
    }
    int getLevel() {
        return level;
    }

    int getXP() {
        return xp;
    }
       void gainXP(int amount) {
        xp += amount;

        while (xp >= xpToLevel && level < maxLevel) {
            xp -= xpToLevel;
            levelUp();
        }
        if (level >= maxLevel) {
        xp = 0;

    }
        
    }
    void levelUp() {
        level++;
        increaseMaxHP(6);
        increaseStrength(1);
        increaseIntellect(2);
    }
    int getGold() {
    return gold;
}

void gainGold(int amount) {
    gold += amount;
}

bool spendGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    }

    return false;
}

void addItem(string itemName) {
    inventory.push_back(itemName);
}

int getInventorySize() {
    return inventory.size();
}

string getItem(int index) {
    if (index >= 0 && index < static_cast<int>(inventory.size())) {
        return inventory[index];
    }

    return "Invalid Item";
}
//Remove Items with specific effects
void removeItem(int index) {
    if (index >= 0 && index < static_cast<int>(inventory.size())) {
        inventory.erase(inventory.begin() + index);
    }
}

    void showInventory() {
        cout << "\n===== INVENTORY =====\n";
        cout << "Gold: " << gold << endl;

        if (inventory.size() == 0) {
            cout << "Your inventory is empty.\n";
        }
        else {
            for (int i = 0; i < inventory.size(); i++) {
                cout << i + 1 << ". " << inventory[i] << endl;
            }
        }
    }
    
    bool useItem(int itemChoice) {
        int index = itemChoice - 1;

        if (index < 0 || index >= static_cast<int>(inventory.size())) {
            cout << "Invalid item choice.\n";
            return false;
        }

        string item = inventory[index];

        if (item == "Health Potion") {
            heal(10);
            cout << "You used a Health Potion and restored 10 HP.\n";

            removeItem(index);
            return true;
        }
        else if (item == "Greater Health Potion") {
            heal(25);
            cout << "You used a Greater Health Potion and restored 25 HP.\n";

            removeItem(index);
            return true;
        }

        cout << item << " can only be used during battle.\n";
        return false;
    }
};

// =============================
// Rogue Class
// Consistent physical damage
// =============================
class Rogue : public hp, public StatBlock {
 private:   
    int level;
    int xp;
    int xpToLevel;
    int maxLevel;
    vector<string> inventory;
    int gold;

    string tarotBlessing;
    int tarotHPBonus;
    int tarotSTRBonus;
    int tarotINTBonus;

public:
    static const hptype HPGROWTH = (hptype)10u;
    static const stattype BASESTR = (stattype)3u;
    static const stattype BASEINT = (stattype)2u;

    void setTarotBlessing(string blessingName) {
    tarotBlessing = blessingName;
    }
    string getTarotBlessing() {
        return tarotBlessing;
    }

    Rogue() : hp(HPGROWTH, HPGROWTH), StatBlock(BASESTR, BASEINT) {
        level = 1;
        xp = 0;
        xpToLevel = 30;
        maxLevel = 8;
        gold = 0;

        tarotBlessing = "None";
        tarotHPBonus = 0;
        tarotSTRBonus = 0;
        tarotINTBonus = 0;
        inventory.push_back("Health Potion");
    }

    void removeTarotEffects() {
        if (tarotHPBonus > 0) {
            setMaxHp(getMaxHP() - tarotHPBonus);
        }

        if (tarotSTRBonus > 0) {
            decreaseStrength(tarotSTRBonus);
        }

        if (tarotINTBonus > 0) {
            decreaseIntellect(tarotINTBonus);
        }

        tarotBlessing = "None";
        tarotHPBonus = 0;
        tarotSTRBonus = 0;
        tarotINTBonus = 0;
    }

    void applyTarotBlessing(string blessingName, int hpBonus, int strBonus, int intBonus) {
        removeTarotEffects();

        tarotBlessing = blessingName;
        tarotHPBonus = hpBonus;
        tarotSTRBonus = strBonus;
        tarotINTBonus = intBonus;

        if (tarotHPBonus > 0) {
            increaseMaxHP(tarotHPBonus);
            heal(tarotHPBonus);
        }

        if (tarotSTRBonus > 0) {
            increaseStrength(tarotSTRBonus);
        }

        if (tarotINTBonus > 0) {
            increaseIntellect(tarotINTBonus);
        }
    }
    int getLevel() {
        return level;
    }

    int getXP() {
        return xp;
    }
       void gainXP(int amount) {
        xp += amount;

        while (xp >= xpToLevel && level < maxLevel) {
            xp -= xpToLevel;
            levelUp();
        }
        if (level >= maxLevel) {
        xp = 0;

    }
        
    }
    void levelUp() {
        level++;
        increaseMaxHP(5);
        increaseStrength(2);
        increaseIntellect(1);
    }
    int getGold() {
    return gold;
}

void gainGold(int amount) {
    gold += amount;
}

bool spendGold(int amount) {
    if (gold >= amount) {
        gold -= amount;
        return true;
    }

    return false;
}

void addItem(string itemName) {
    inventory.push_back(itemName);
}
//Remove Items with specific effects
void removeItem(int index) {
    if (index >= 0 && index < static_cast<int>(inventory.size())) {
        inventory.erase(inventory.begin() + index);
    }
}

int getInventorySize() {
    return inventory.size();
}

string getItem(int index) {
    if (index >= 0 && index < static_cast<int>(inventory.size())) {
        return inventory[index];
    }

    return "Invalid Item";
}

    void showInventory() {
        cout << "\n===== INVENTORY =====\n";
        cout << "Gold: " << gold << endl;

        if (inventory.size() == 0) {
            cout << "Your inventory is empty.\n";
        }
        else {
            for (int i = 0; i < inventory.size(); i++) {
                cout << i + 1 << ". " << inventory[i] << endl;
            }
        }
    }

    bool useItem(int itemChoice) {
        int index = itemChoice - 1;

        if (index < 0 || index >= static_cast<int>(inventory.size())) {
            cout << "Invalid item choice.\n";
            return false;
        }

        string item = inventory[index];

        if (item == "Health Potion") {
            heal(10);
            cout << "You used a Health Potion and restored 10 HP.\n";

            removeItem(index);
            return true;
        }
        else if (item == "Greater Health Potion") {
            heal(25);
            cout << "You used a Greater Health Potion and restored 25 HP.\n";

            removeItem(index);
            return true;
        }

        cout << item << " can only be used during battle.\n";
        return false;
    }
    
};