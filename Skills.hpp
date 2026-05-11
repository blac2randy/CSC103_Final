#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Skill {
    

public:
    string name;
    string description;
    string statUsed;   // "STR" or "INT" or "BOTH"
    int unlockLevel;
    int bonusDamage;

    Skill(string skillName, string skillDescription, string stat, int level, int bonus) {
        name = skillName;
        description = skillDescription;
        statUsed = stat;
        unlockLevel = level;
        bonusDamage = bonus;
    }

};
vector<Skill> getWarriorSkills() {

    vector<Skill> skills;

    skills.push_back(Skill("Slash", "A basic sword attack.", "STR", 1, 0));
    skills.push_back(Skill("Heavy Strike", "A stronger attack from above", "STR", 2, 3));
    skills.push_back(Skill("Shield Bash", "A crushing shield attack.", "STR", 4, 5));
    skills.push_back(Skill("Cleave", "A wide powerful swing.", "STR", 6, 8));
    skills.push_back(Skill("Menacing Attack", "Bellow from the chest and strike with all your might", "STR", 8, 12));

    return skills;

}

vector<Skill> getWizardSkills() {

    vector<Skill> skills;

    skills.push_back(Skill("Ignis", "A small burst of fire magic", "INT", 1, 0));
    skills.push_back(Skill("WildBurst", "A burning magical projectile.", "INT", 2, 3));
    skills.push_back(Skill("Ice shard", "A sharp spear of ice.", "INT", 4, 5));
    skills.push_back(Skill("Arcane Burst", "A blast of unstable magic.", "INT", 6, 8));
    skills.push_back(Skill("Eldritch Blast", "Call apon your patron and fire a beam of forbidden magic untold.", "INT", 8, 12));
    return skills;

}

vector<Skill> getClericSkills() {

    vector<Skill> skills;
    skills.push_back(Skill("Staff Strike", "You hit them with a stick.", "STR", 1, 0));
    skills.push_back(Skill("Cast", "Infused attack with the power of God.", "INT", 2, 3));
    skills.push_back(Skill("Smite", "A focused holy attack.", "INT", 4, 5));
    skills.push_back(Skill("Blessed Hammer", "A strike empowered by faith.", "BOTH", 6, 0));
    skills.push_back(Skill("Divine Judgment", "A powerful holy finishing spell.", "INT", 8, 12));
    return skills;

}

vector<Skill> getRogueSkills() {

    vector<Skill> skills;
    skills.push_back(Skill("Quick Stab", "A fast dagger attack.", "STR", 1, 0));
    skills.push_back(Skill("Backstab", "A precise strike at a weak point.", "STR", 2, 3));
    skills.push_back(Skill("Poison Cut", "A dirty blade attack.", "STR", 4, 5));
    skills.push_back(Skill("Shadow Strike", "A strike from the darkness.", "BOTH", 6, 0));
    skills.push_back(Skill("Assassinate", "A deadly finishing attack.", "STR", 8, 12));

    return skills;

}
void showAvailableSkills(vector<Skill> skills, int playerLevel) {

    cout << "\n===== AVAILABLE SKILLS =====\n";
    for (int i = 0; i < skills.size(); i++) {
        if (playerLevel >= skills[i].unlockLevel) {
            cout << i + 1 << ". " << skills[i].name << "\n";
            cout << "   " << skills[i].description << "\n";
            cout << "   Uses: " << skills[i].statUsed
                 << " | Unlock Level: " << skills[i].unlockLevel
                 << " | Bonus Damage: +" << skills[i].bonusDamage << "\n\n";
        }

    }
}
int calculateSkillDamage(Skill skill, int strength, int intellect) {

    if (skill.statUsed == "STR") {
        return strength + skill.bonusDamage;
    }
    else if (skill.statUsed == "INT") {
        return intellect + skill.bonusDamage;
    }
    else if (skill.statUsed == "BOTH") {
        return strength + intellect + skill.bonusDamage;
    }
    return strength;
}



