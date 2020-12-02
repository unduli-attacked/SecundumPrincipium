// CSCI Fall 2020
// Author: Jocelyn McHugo
// Recitation: 318 - Maria Stull
// [assignment] -- Problem #[]

#include "TeamMember.h"
#include "User.h"

User::User() {
    firstName = "John";
    lastName = "Sheppard";
    teamConf = 100;
    health = 10;
    teamSlotsFilled = 0;
    progress = 0;

    generateSkills();
}

User::User(string firstName_, string lastName_) {
    firstName = firstName_;
    lastName = lastName_;
    teamConf = 100;
    health = 10;
    teamSlotsFilled = 0;
    progress = 0;

    generateSkills();
}

string User::getFirstName() {
    return firstName;
}

void User::setFirstName(string firstName_) {
    firstName = firstName_;
}

string User::getLastName() {
    return lastName;
}

void User::setLastName(string lastName_) {
    lastName = lastName_;
}

void User::generateSkills() {
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

void User::updateSkill(Skill newSkill) {
    for (int i = 0; i < NUM_SKILLS; i++) {
        if (skills[i].getSkillName() == newSkill.getSkillName()) {
            skills[i] = newSkill;
        }
    }
}

Skill User::getSkill(string skillName_) {
    for (int i = 0; i < NUM_SKILLS; i++) {
        if (skills[i].getSkillName() == skillName_) {
            return skills[i];
        }
    }
}

int User::addTeamMember(TeamMember member_) {
    if (teamSlotsFilled < TEAM_SLOTS) {
        team[teamSlotsFilled] = member_;
        teamSlotsFilled++;
        return teamSlotsFilled;
    } else {
        return -1;
    }
}

int User::removeTeamMember(TeamMember member_) {
    int index = -1;
    for (int i = 0; i < teamSlotsFilled; i++) {
        if (team[i].equals(member_)) { //TODO check
            team[i] = TeamMember();
            index = i;
            i = teamSlotsFilled;
        }
    }
    if (index != -1) {
        for (int i = index; i < TEAM_SLOTS - 1; i++) {
            team[i] = team[i + 1];
        }
        team[TEAM_SLOTS - 1] = TeamMember();
        teamSlotsFilled--;
        return 1;
    }
    return -1;
}

TeamMember User::getTeamMember(string first_, string last_) {
    for (int i = 0; i < teamSlotsFilled; i++) {
        if (team[i].getFirstName() == first_ && team[i].getLastName() == last_) {
            return team[i];
        }
    }
    return TeamMember();
}

TeamMember User::getTeamMember(int index) {
    return team[index];
}

int User::getHighestSkillLevel(string skillName) {
    int highestLevel = 0;
    for (TeamMember teamMember : team) {
        if (teamMember.getSkill(skillName).getSkillLevel() > highestLevel) {
            highestLevel = teamMember.getSkill(skillName).getSkillLevel();
        }
    }
    if (getSkill(skillName).getSkillLevel() > highestLevel) {
        return getSkill(skillName).getSkillLevel();
    }
    return highestLevel;
}

TeamMember User::getLowestSkilled(string skillName) {
    int lowestLevel = 0;
    TeamMember lowestMember;
    for (TeamMember teamMember : team) {
        if (teamMember.getSkill(skillName).getSkillLevel() < lowestLevel) {
            lowestLevel = teamMember.getSkill(skillName).getSkillLevel();
            lowestMember = teamMember;
        }
    }
    return lowestMember;
}

TeamMember User::getHighestSkilled(string skillName) {
    int highestLevel = 0;
    TeamMember highestMember;
    for (TeamMember teamMember : team) {
        if (teamMember.getSkill(skillName).getSkillLevel() > highestLevel) {
            highestLevel = teamMember.getSkill(skillName).getSkillLevel();
            highestMember = teamMember;
        }
    }
    if (getSkill(skillName).getSkillLevel() > highestLevel) {
        return *this; //TODO hope this works
    }
    return highestMember;
}

int User::getTeamConf() {
    return teamConf;
}

void User::setTeamConf(int conf_) {
    if (conf_ >= 0 && conf_ < 100) {
        teamConf = conf_;
    }
}

int User::getHealth() {
    return health;
}

void User::setHealth(int health_) {
    if (health_ >= 0 && health_ < 10) {
        health = health_;
    }
}

int User::getTeamSlotsFilled() {
    return teamSlotsFilled;
}

int User::getProgress() {
    return progress;
}

void User::setProgress(int prog_) {
    if (prog_ >= 0 && prog_ < 10) {
        progress = prog_;
    }
}

string User::format() {
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