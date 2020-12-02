// CSCI Fall 2020
// Author: Jocelyn McHugo
// Recitation: 318 - Maria Stull
// [assignment] -- Problem #[]

#include "Gear.h"

Gear::Gear() {
    slotsFilled = 0;
}

Gear::Gear(string *inventory_, int slotsFilled_) {
    for (int i = 0; i < slotsFilled_; i++) {
        inventory[i] = inventory_[i];
    }
    slotsFilled = slotsFilled_;
}

int Gear::getSlotsFilled() {
    return slotsFilled;
}

int Gear::fillSlot(string newItem_) {
    if (slotsFilled <= GEAR_SLOTS) {
        inventory[slotsFilled] = newItem_;
        slotsFilled++;
        return slotsFilled;
    } else {
        return -1;
    }
}

int Gear::countItems(string itemName_) {
    int count = 0;
    for (int i = 0; i < slotsFilled; i++) {
        if (inventory[i] == itemName_) {
            count++;
        }
    }
    return count;
}

string Gear::getItem(int index_) {
    return inventory[index_];
}

int Gear::useItem(string itemName_) {
    int index = -1;
    for (int i = 0; i < slotsFilled; i++) {
        if (inventory[i] == itemName_) {
            inventory[i] = "";
            index = i;
            i = slotsFilled;
        }
    }
    if (index != -1) {
        for (int i = index; i < GEAR_SLOTS - 1; i++) {
            inventory[i] = inventory[i + 1];
        }
        inventory[GEAR_SLOTS - 1] = "";
        slotsFilled--;
        return 1;
    }
    return -1; //none found
}

string Gear::format() {
    string str = "Inventory:\n";
    for (int i = 0; i < GEAR_SLOTS; i += 4) {
        for (int j = 0; j < 3; j++) {
            if (inventory[i + j] == "") {
                str += "[      ], ";
            } else {
                str += "[" + inventory[i + j] + "], ";
            }
        }
        if (inventory[i + 3] == "") {
            str += "[      ]\n";
        } else {
            str += "[" + inventory[i + 3] + "]\n";
        }
    }
    return str;
}

bool Gear::hasMedKit() {
    return countItems("medicalKit") > 0;
}

bool Gear::hasWeapons() {
    return countItems("weapons") > 0;
}

bool Gear::hasStarChart() {
    return countItems("starChart") > 0;
}

bool Gear::hasDivingGear() {
    return countItems("divingGear") > 0;
}

bool Gear::hasScanner() {
    return countItems("scanner") > 0;
}