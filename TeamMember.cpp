// CSCI Fall 2020
// Author: Jocelyn McHugo
// Recitation: 318 - Maria Stull
// [assignment] -- Problem #[]

#include "TeamMember.h"

TeamMember::TeamMember() {
    firstName = "";
    lastName = "";
}

TeamMember::TeamMember(string firstName_, string lastName_) {
    firstName = firstName_;
    lastName = lastName_;

    generateSkills();
}

string TeamMember::getFirstName() {
    return firstName;
}

void TeamMember::setFirstName(string firstName_) {
    firstName = firstName_;
}

string TeamMember::getLastName() {
    return lastName;
}

void TeamMember::setLastName(string lastName_) {
    lastName = lastName_;
}

void TeamMember::generateSkills() {
    skills[0] = Skill("strength", rand() % 11);
    skills[1] = Skill("dexterity", rand() % 11);
    skills[2] = Skill("intelligence", rand() % 11);
    skills[3] = Skill("instinct", rand() % 11);
    skills[4] = Skill("charisma", rand() % 11);
    skills[5] = Skill("swimming", rand() % 11);
    skills[6] = Skill("medical", rand() % 11);
    skills[7] = Skill("technology", rand() % 11);
    skills[8] = Skill("bartering", rand() % 11);
    skills[9] = Skill("combat", rand() % 11);
    skills[10] = Skill("navigation", rand() % 11);
    skills[11] = Skill("earnestness", rand() % 11);
}

void TeamMember::updateSkill(Skill newSkill) {
    for (int i = 0; i < NUM_SKILLS; i++) {
        if (skills[i].getSkillName() == newSkill.getSkillName()) {
            skills[i] = newSkill;
        }
    }
}

Skill TeamMember::getSkill(string skillName_) {
    for (int i = 0; i < NUM_SKILLS; i++) {
        if (skills[i].getSkillName() == skillName_) {
            return skills[i];
        }
    }
}

Skill TeamMember::getSkill(int index_) {
    if (index_ >= 0 && index_ < NUM_SKILLS) {
        return skills[index_];
    }
}

bool TeamMember::equals(TeamMember other) {
    bool equal;
    equal = (firstName == other.getFirstName()) && (lastName == other.getLastName());
    for (int i = 0; i < NUM_SKILLS; i++) {
        equal = equal && skills[i].getSkillName() == other.getSkill(i).getSkillName() && skills[i].getSkillLevel() == other.getSkill(i).getSkillLevel();
    }
    return equal;
}

string TeamMember::format() {
    string str = firstName + " " + lastName;
    str += "\n--------------------\n";
    for (int i = 0; i < NUM_SKILLS; i++) {
        str += skills[i].getSkillName();
        str += ": ";
        str += to_string(skills[i].getSkillLevel());
        str += "\n";
    }
    return str;
}