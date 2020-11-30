// CSCI Fall 2020
// Author: Jocelyn McHugo
// Recitation: 318 - Maria Stull
// [assignment] -- Problem #[]

#ifndef SECUNDUMPRINCIPUM_GEAR_H
#define SECUNDUMPRINCIPUM_GEAR_H

#include <string>

using namespace std;

class Gear {
public:
    Gear();

    Gear(string inventory_[], int slotsFilled_);

    int getSlotsFilled();

    int fillSlot(string newItem_);

    int countItems(string itemName_); // number of instances of an item
    string getItem(int index_);

    int useItem(string itemName_);

    string format();

    bool hasMedKit();

    bool hasWeapons();

    bool hasStarChart();

    bool hasDivingGear();

    bool hasScanner();

private:
    static const int GEAR_SLOTS = 12; //change later
    int slotsFilled;
    string inventory[GEAR_SLOTS]; // list of items
};


#endif //SECUNDUMPRINCIPUM_GEAR_H
