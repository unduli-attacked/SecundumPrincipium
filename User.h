// CSCI Fall 2020
// Author: Jocelyn McHugo
// Recitation: 318 - Maria Stull
// [assignment] -- Problem #[]

#ifndef SECUNDUMPRINCIPUM_USER_H
#define SECUNDUMPRINCIPUM_USER_H


#include "TeamMember.h"
#include "Gear.h"
#include "Skill.h"
#include <string>

using namespace std;

class User : public TeamMember{
public:
    User();

    User(string firstName_, string lastName_, Skill skills[], int teamConf_, int health_, int teamSlotsFilled_,
         Gear inventory_, TeamMember team_[], int progress_);

    User(string firstName, string lastName_);

    int addTeamMember(TeamMember member_);

    int removeTeamMember(TeamMember member_);

    TeamMember getTeamMember(string first_, string last_);
    TeamMember getTeamMember(int index);
    int getHighestSkillLevel(string skillName);
    TeamMember getLowestSkilled(string skillName);
    TeamMember getHighestSkilled(string skillName);
    int getTeamConf();

    void setTeamConf(int conf_);

    int getHealth();

    void setHealth(int health_);

    int getTeamSlotsFilled();

    int getProgress();

    void setProgress(int prog_);

    string getFirstName();

    void setFirstName(string firstName_);

    string getLastName();

    void setLastName(string lastName_);

    void generateSkills();

    void updateSkill(Skill newSkill);

    Skill getSkill(string skillName_);

    string format();

private:
    int teamConf;
    int health;
    static const int TEAM_SLOTS = 6;
    int teamSlotsFilled;
    TeamMember team[TEAM_SLOTS];
    int progress; // out of 10
    static const int NUM_SKILLS = 12;
    string firstName;
    string lastName;
    Skill skills[NUM_SKILLS];
};


#endif //SECUNDUMPRINCIPUM_USER_H
