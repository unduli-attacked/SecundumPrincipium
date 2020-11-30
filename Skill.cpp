// CSCI Fall 2020
// Author: Jocelyn McHugo
// Recitation: 318 - Maria Stull
// [assignment] -- Problem #[]

#include "Skill.h"

Skill::Skill() {
    skillName = "";
    skillLevel = 0;
}

Skill::Skill(string skillName_) {
    skillName = skillName_;
    skillLevel = 0;

    if (skillName_ == "medical") {
        boostedBy = "medicalKit";
    } else if (skillName_ == "bartering") {
        boostedBy = "tradeableGoods";
    } else if (skillName_ == "combat") {
        boostedBy = "weapons";
    } else if (skillName_ == "navigation") {
        boostedBy = "starChart";
    } else {
        boostedBy = "";
    }
}

Skill::Skill(string skillName_, int skillLevel_) {
    skillName = skillName_;
    skillLevel = skillLevel_;

    if (skillName_ == "medical") {
        boostedBy = "medicalKit";
    } else if (skillName_ == "bartering") {
        boostedBy = "tradeableGoods";
    } else if (skillName_ == "combat") {
        boostedBy = "weapons";
    } else if (skillName_ == "navigation") {
        boostedBy = "starChart";
    }else if(skillName_=="technology"){
        boostedBy = "scanner";
    } else {
        boostedBy = "";
    }
}

string Skill::getSkillName() {
    return skillName;
}

int Skill::getSkillLevel() {
    return skillLevel;
}

void Skill::setSkillLevel(int skillLevel_) {
    if (skillLevel_ >= 0) {
        skillLevel = skillLevel_;
    }
}

string Skill::getBoost() {
    return boostedBy;
}