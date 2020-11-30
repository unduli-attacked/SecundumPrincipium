// CSCI Fall 2020
// Author: Jocelyn McHugo
// Recitation: 318 - Maria Stull
// [assignment] -- Problem #[]

#ifndef SECUNDUMPRINCIPUM_TEAMMEMBER_H
#define SECUNDUMPRINCIPUM_TEAMMEMBER_H

#include <string>
#include "Skill.h"

using namespace std;

class TeamMember {
public:
    TeamMember();

    TeamMember(string firstName_, string lastName_);

    string getFirstName();

    void setFirstName(string firstName_);

    string getLastName();

    void setLastName(string lastName_);

    void generateSkills();

    void updateSkill(Skill newSkill);

    Skill getSkill(string skillName_);

    Skill getSkill(int index_);

    bool equals(TeamMember other);

    string format();

private:
    static const int NUM_SKILLS = 12;
    string firstName;
    string lastName;
    Skill skills[NUM_SKILLS];
};


#endif //SECUNDUMPRINCIPUM_TEAMMEMBER_H
