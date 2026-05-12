#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Skill {
public:
    string name;
    string description;
    string effectType;
    int unlockLevel;
    int value;
    int duration;
    int cooldown;
    int currentCooldown;

    Skill(string skillName, string skillDescription, string effect,
          int level, int skillValue, int skillDuration, int skillCooldown) {
        name = skillName;
        description = skillDescription;
        effectType = effect;
        unlockLevel = level;
        value = skillValue;
        duration = skillDuration;
        cooldown = skillCooldown;
        currentCooldown = 0;
    }
};


vector<Skill> getWarriorSkills() {
    vector<Skill> skills;

    skills.push_back(Skill("Slash", "A basic sword attack.", "STR_DAMAGE", 1, 0, 0, 0));
    skills.push_back(Skill("Multi Cut", "Attack twice with quick sword strikes.", "MULTI_HIT", 2, 2, 0, 2));
    skills.push_back(Skill("Guard", "Enemies deal 30% less damage for 3 turns.","REDUCE_DAMAGE_TAKEN", 4, 30, 3, 5));
    skills.push_back(Skill("Heavy Slash", "A powerful slash that deals 3x basic Strength damage.", "STR_MULTIPLIER", 6, 3, 0, 3));
    skills.push_back(Skill("Battle Cry", "Increase skill damage by 20% for 2 turns.", "BOOST_DAMAGE", 8, 20, 2, 5));
    
    return skills;
}

vector<Skill> getWizardSkills() {
    vector<Skill> skills;

    skills.push_back(Skill("Ignis", "A small burst of fire magic.", "INT_DAMAGE", 1, 0, 0, 0));
    skills.push_back(Skill("Wind Cutter", "A slicing burst of wind that deals 6 damage.", "FLAT_DAMAGE", 2, 6, 0, 2));
    skills.push_back(Skill("Witch Bolt", "A bolt of lightning that deals 10 damage.", "FLAT_DAMAGE", 4, 10, 0, 3));
    skills.push_back(Skill("Shield", "Enemies deal 30% less damage for 3 turns.", "REDUCE_DAMAGE_TAKEN", 6, 30, 3, 5));
    skills.push_back(Skill("Light Cannon", "A concentrated beam of magic that deals 20 damage.", "FLAT_DAMAGE", 8, 20, 0, 5));

    return skills;
}

vector<Skill> getClericSkills() {
    vector<Skill> skills;

    skills.push_back(Skill("Shillelagh Strike", "You hit them with a stick.", "STR_DAMAGE", 1, 0, 0, 0));
    skills.push_back(Skill("Prayer", "Heal 40% of your max HP.", "HEAL_PERCENT", 2, 40, 0, 3));
    skills.push_back(Skill("Sloth", "Enemies deal 40% less damage for 4 turns.", "REDUCE_DAMAGE_TAKEN", 4, 40, 4, 5));
    skills.push_back(Skill("Sacred Flame", "Deal basic damage plus 30% of the enemy's max HP.", "STR_PLUS_PERCENT", 6, 30, 0, 4));
    skills.push_back(Skill("Bless", "Heal 80% of your max HP.", "HEAL_PERCENT", 8, 80, 0, 5));

    return skills;
}

vector<Skill> getRogueSkills() {
    vector<Skill> skills;

    skills.push_back(Skill("Quick Step", "A fast dagger attack.", "STR_DAMAGE", 1, 0, 0, 0));
    skills.push_back(Skill("Backstab", "A precise strike that deals 8 damage.", "FLAT_DAMAGE", 2, 8, 0, 2));
    skills.push_back(Skill("Finesse", "Deal 20% more damage and receive 20% less damage for 3 turns.", "BOOST_AND_REDUCE", 4, 20, 3, 5));
    skills.push_back(Skill("Dirty Trick", "A cowardly attack from the shadows dealing 12 damage.", "FLAT_DAMAGE", 6, 12, 0, 3));
    skills.push_back(Skill("Frontal Assault", "A direct assault that deals 15 damage.", "FLAT_DAMAGE", 8, 15, 0, 4));

    return skills;
}

void showAvailableSkills(vector<Skill> skills, int playerLevel) {
    cout << "\n===== AVAILABLE SKILLS =====\n";
    for (int i = 0; i < static_cast<int>(skills.size()); i++) {
        if (playerLevel >= skills[i].unlockLevel) {
            cout << i + 1 << ". " << skills[i].name << "\n";
            cout << "   " << skills[i].description << "\n";
            cout << "   Unlock Level: " << skills[i].unlockLevel;
            cout << " | Cooldown: " << skills[i].cooldown;
            if (skills[i].currentCooldown > 0) {
                cout << " | Locked for " << skills[i].currentCooldown << " turn(s)";
            }
            cout << "\n\n";
        }
    }
}
int percentDamage(int targetMaxHP, int percent) {
    int damage = targetMaxHP * percent / 100;

    if (damage < 1) {
        damage = 1;
    }

    return damage;
}

//Skill damage calculator, hardest part to determine for the game tbh
int calculateSkillDamage(Skill skill, int strength, int intellect, int enemyMaxHP) {
    if (skill.effectType == "STR_DAMAGE") {
        return strength + skill.value;
    }
    else if (skill.effectType == "INT_DAMAGE") {
        return intellect + skill.value;
    }
    else if (skill.effectType == "BOTH_DAMAGE") {
        return strength + intellect + skill.value;
    }
    else if (skill.effectType == "FLAT_DAMAGE") {
        return skill.value;
    }
    else if (skill.effectType == "PERCENT_ENEMY_HP") {
        return percentDamage(enemyMaxHP, skill.value);
    }
    else if (skill.effectType == "MULTI_HIT") {
        return strength * skill.value;
    }
    else if (skill.effectType == "STR_MULTIPLIER") {
        return strength * skill.value;
    }
    else if (skill.effectType == "STR_PLUS_PERCENT") {
        return strength + percentDamage(enemyMaxHP, skill.value);
    }
    return strength;
}




