// CSCI Fall 2020
// Author: Jocelyn McHugo
// Recitation: 318 - Maria Stull
// [assignment] -- Problem #[]

#ifndef SECUNDUMPRINCIPUM_SKILL_H
#define SECUNDUMPRINCIPUM_SKILL_H

#include <string>
#include <vector>

using namespace std;

class Skill {
public:
    Skill();

    Skill(string skillName_); // auto-generate skill level
    Skill(string skillName_, int skillLevel_);

    string getSkillName();

    int getSkillLevel();

    void setSkillLevel(int skillLevel_);

    string getBoost();

private:
    string skillName;
    int skillLevel;
    string boostedBy;
};


#endif //SECUNDUMPRINCIPUM_SKILL_H
