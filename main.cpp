#include <iostream>
#include "TeamMember.h"
#include "User.h"
#include <iomanip>
#include <fstream>

using namespace std;
User player;
Gear inventory;

void printTeam(int numPerRow, TeamMember community[]){
    string str = "";
    for (int i = 0; i < 12; i += numPerRow) {
        for (int j = 0; j < numPerRow; j++) {
            str = to_string(i + j + 1) + ": " + community[i + j].getFirstName() + " " + community[i + j].getLastName();
            cout << left << setw(22) << str;
        }
        cout << endl;
        for (int j = 0; j < numPerRow; j++) {
            cout << left << setw(22) << "--------------------";
        }
        cout << endl;
        for (int k = 0; k < 12; k++) {
            for (int j = 0; j < numPerRow; j++) {
                str = community[i + j].getSkill(k).getSkillName() + ": " + to_string(community[i + j].getSkill(k).getSkillLevel());
                cout << left << setw(22) << str;
            }
            cout << endl;
        }
        cout << endl;
    }
}

bool manOverboard() {
    TeamMember manOverboard = player.getLowestSkilled("dexterity");
    cout << "You have departed your flotilla with your team and begun your journey" << endl;
    cout << "As you are travelling, " << manOverboard.getFirstName() << " falls overboard." << endl;
    if (player.getHighestSkillLevel("swimming") > 5) {
        cout << player.getHighestSkilled("swimming").getFirstName() << " is the best swimmer on your team, and they are able to bring " << manOverboard.getFirstName() << " back aboard." << endl;
        if (player.getHighestSkillLevel("medical") > 7) {
            cout << player.getHighestSkilled("medical").getFirstName() << " is the best medic on your team, and are able to revive " << manOverboard.getFirstName() << ". Your journey continues."
                 << endl;
            return false;
        } else if (player.getHighestSkillLevel("medical") + 3 > 7 && inventory.hasMedKit()) {
            inventory.useItem("medicalKit");
            cout << player.getHighestSkilled("medical").getFirstName() << " is the best medic on your team, and is able to revive " << manOverboard.getFirstName()
                 << " with the help of one of your medical kits. Your journey continues." << endl;
            return false;
        } else {
            cout << manOverboard.getFirstName() << " is back aboard the boat, but your team is unable to revive them." << endl;
            cout << manOverboard.getFirstName() << " drowns, and your team loses confidence in you, but you continue on your journey." << endl;
            player.removeTeamMember(manOverboard);
            player.setTeamConf(player.getTeamConf() - 20);
            return false;
        }
    } else if (player.getHighestSkillLevel("swimming") < 2) {
        cout << player.getHighestSkilled("swimming").getFirstName() << " is the best swimmer on your team, but they are unable to save " << manOverboard.getFirstName() << "." << endl;
        cout << manOverboard.getFirstName() << " drowns, and your team loses confidence in you." << endl;
        cout << "Because " << player.getHighestSkilled("swimming").getFirstName()
             << " is not a very good swimmer, they also drown, and your team loses even more confidence in you, but you continue on your journey." << endl;
        player.removeTeamMember(manOverboard);
        player.setTeamConf(player.getTeamConf() - 40);
        return false;
    } else {
        cout << player.getHighestSkilled("swimming").getFirstName() << " is the best swimmer on your team, but they are unable to save " << manOverboard.getFirstName() << "." << endl;
        cout << manOverboard.getFirstName() << " drowns, and your team loses confidence in you, but you continue on your journey." << endl;
        player.removeTeamMember(manOverboard);
        player.setTeamConf(player.getTeamConf() - 20);
        return false;
    }
}

bool raiders(){
    int choice = 0;
    cout << "Your boat is ambushed by raiders!" << endl;
    while (true){
        cout << "You have two options:\n1. Barter for your freedom\n2. Try to fight them off" << endl;
        cin >> choice;
        switch (choice){
            case 1:
                if (player.getHighestSkillLevel("charisma") + player.getHighestSkillLevel("bartering") > 8) {
                    cout << player.getHighestSkilled("charisma").getFirstName() << ", and " << player.getHighestSkilled("bartering").getFirstName() << ", and "
                         << " are able to convince the raiders, who are sympathetic to your quest, to let you go." << endl;
                    return false;
                } else if (player.getHighestSkillLevel("charisma") + player.getHighestSkillLevel("bartering") + 5 > 8  &&
                           inventory.countItems("tradeableGoods") > 0) {
                    cout << player.getHighestSkilled("charisma").getFirstName() << ", and " << player.getHighestSkilled("bartering").getFirstName() << ", and "
                         << " are able to convince the raiders to let you go by giving them one of your Tradeable Goods."
                         << endl;
                    inventory.useItem("tradeableGoods");
                    return false;
                } else {
                    cout << "You are unable to persuade the raiders to let you go." << endl;
                    return true;
                }
                break;
            case 2:
                if(player.getHighestSkillLevel("combat") > 7){
                    cout << "You are able to fight off the raiders, winning your freedom to continue your quest." << endl;
                    cout << "However, " << player.getLowestSkilled("strength").getFirstName() << " is killed in the fighting, and your team's confidence in you is reduced." << endl;
                    player.removeTeamMember(player.getLowestSkilled("strength"));
                    player.setTeamConf(player.getTeamConf()-20);
                    return false;
                }else if(player.getHighestSkillLevel("combat") + 3 > 7 && inventory.hasWeapons()){
                    cout << "You are able to fight off the raiders using one of your Weapons, winning your freedom to continue your quest." << endl;
                    cout << "However, " << player.getLowestSkilled("strength").getFirstName() << " is killed in the fighting, and your team's confidence in you is reduced." << endl;
                    player.removeTeamMember(player.getLowestSkilled("strength"));
                    inventory.useItem("weapons");
                    player.setTeamConf(player.getTeamConf()-20);
                    return false;
                }else{
                    cout << "You are unable to fight off the raiders, and your team is killed." << endl;
                    return true;
                }
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    }
}

bool witches() {
    int methodChoice = 0;
    cout << "As you travel, you come across a band of witches." << endl;
    cout << "According to legend, these witches likely know how to find the Secundum Principium." << endl;
    while(true) {
        cout << "You have two choices:\n1. Barter with and convince the witches to give you the coordinates\n2. Attack and force the witches to give you the coordinates" << endl;
        cin >> methodChoice;
        switch (methodChoice) {
            case 1:
                if (player.getHighestSkillLevel("charisma") + player.getHighestSkillLevel("bartering") > 8 && player.getHighestSkillLevel("earnestness") > 6) {
                    cout << player.getHighestSkilled("charisma").getFirstName() << ", " << player.getHighestSkilled("bartering").getFirstName() << ", and "
                         << player.getHighestSkilled("earnestness").getFirstName() << " are able to convince the witches to give you the coordinates." << endl;
                    return false;
                } else if (player.getHighestSkillLevel("charisma") + player.getHighestSkillLevel("bartering") + 3 > 8 && player.getHighestSkillLevel("earnestness") > 6 &&
                           inventory.countItems("tradeableGoods") > 0) {
                    cout << player.getHighestSkilled("charisma").getFirstName() << ", " << player.getHighestSkilled("bartering").getFirstName() << ", and "
                         << player.getHighestSkilled("earnestness").getFirstName() << " are able to convince the witches to give you the coordinates by giving them one of your Tradeable Goods."
                         << endl;
                    inventory.useItem("tradeableGoods");
                    return false;
                } else {
                    cout << "You are unable to persuade the witches to give you the coordinates." << endl;
                    return true;
                }
                break;
            case 2:
                if (player.getHighestSkillLevel("combat") == 10 && inventory.countItems("weapons") > 2) {
                    cout << "You attempt to fight the witches. Three of your team members are killed in the process, but you get the coordinates of the Secundum Principium." << endl;
                    player.removeTeamMember(player.getLowestSkilled("combat"));
                    player.removeTeamMember(player.getLowestSkilled("combat"));
                    player.removeTeamMember(player.getLowestSkilled("combat"));
                    inventory.useItem("weapons");
                    inventory.useItem("weapons");
                    player.setTeamConf(player.getTeamConf() - 60);
                    return false;
                } else {
                    cout << "You attempt to fight the witches. All team members except you are killed. Ashamed of your decision to fight, you spend the rest of your life wandering the seas alone."
                         << endl;
                    return true;
                }
                break;
            default:
                cout << "Invalid choice" << endl;
        }
    }
}

bool navigation(){
    int choice = 0;
    cout << "With the coordinates given to you by the witches, you must navigate to the location of the Secundum Principium" << endl;
    cout << "Your team has a navigation level of " << player.getHighestSkillLevel("navigation");
    if(inventory.hasStarChart()){
        cout << ", boosted by your Star Chart, ";
    }else{
        cout << ", ";
    }
    cout << "and an instinct level of " << player.getHighestSkillLevel("instinct") << endl;
    while (true) {
        cout << "You can do one of two things: " << endl;
        cout << "1. Find the location using navigation skills\n2. Find the location on instinct" << endl;
        cin >> choice;
        switch (choice){
            case 1:
                if(player.getHighestSkillLevel("navigation")>8){
                    cout << player.getHighestSkilled("navigation").getFirstName() << " uses their navigation skills to find the Secundum Principium." << endl;
                    return false;
                }else if(player.getHighestSkillLevel("navigation")+3 > 8 && inventory.hasStarChart()){
                    cout << player.getHighestSkilled("navigation").getFirstName() << " uses the Star Chart to find the Secundum Principum." << endl;
                    return false;
                }else{
                    cout << "You are unable to navigate to the Secundum Principium." << endl;
                    return true;
                }
                break;
            case 2:
                if(player.getHighestSkillLevel("instinct") + (rand() %11) > 15){
                    cout << "By some miracle, you've guessed your way to the Secundum Principium!" << endl;
                    return false;
                }else{
                    cout << "You were unable to find the Secundum Principium." << endl;
                    return true;
                }
                break;
            default:
                cout << "Invalid input" << endl;
        }
    }
}

bool submersion(){
    cout << "You have made it to the location of the Secundum Principium! However, it is now clear to you that the doorway itself lies underwater." << endl;
    if(inventory.countItems("divingGear")>1) {
        int numTeam = inventory.countItems("divingGear") - 1;
        cout << "You have " << inventory.countItems("divingGear") << " sets of diving gear, which means only " << numTeam << "members of your team can go down with you."
             << endl;
        cout << "You must select " << numTeam << " members of your team to go with you. Review you team's skills below:" << endl;
        int elimChoice = 0;
        while(player.getTeamSlotsFilled() > numTeam){
            TeamMember tempTeam[6];
            for(int i=0; i<player.getTeamSlotsFilled(); i++){
                tempTeam[i] = player.getTeamMember(i);
            }
            printTeam(3, tempTeam);
            cout << "Select a team member to LEAVE BEHIND. (1-" << player.getTeamSlotsFilled() << endl;
            cin >>elimChoice;
            if(elimChoice > 0 && elimChoice < player.getTeamSlotsFilled()) {
                cout << player.getTeamMember(elimChoice-1).getFirstName() << " " << player.getTeamMember(elimChoice-1).getLastName() << " has been left behind." << endl;
                player.removeTeamMember(player.getTeamMember(elimChoice - 1));
            }else{
                cout << "Invalid input" << endl;
            }
        }
        return false;
    }else if(inventory.countItems("divingGear")>0){
        cout << "You only have 1 set of diving gear, so you must dive alone." << endl;
        for(int i=0; i<player.getTeamSlotsFilled(); i++){
            player.removeTeamMember(player.getTeamMember(i));
        }
        return false;
    }else{
        cout << "You have no diving gear. You cannot reach the Secundum Principium." << endl;
        return true;
    }
}

bool oneFalseStep(){
    cout << "You and your smaller team dive down and find a sealed airlock just a few dozen feet below the surface." << endl;
    cout << "You open the door and flush the water out, enabling you all to take off your diving gear." << endl;
    while(inventory.hasDivingGear()){
        inventory.useItem("divingGear");
    }
    cout << "The hallway beyond the airlock is in shadow, and likely contains many booby traps. To navigate it, you must use a combination of the following skills:\n"
    << "1. Intelligence: Level " << player.getHighestSkillLevel("intelligence")
    << "\n2. Instinct: Level " << player.getHighestSkillLevel("instinct")
    << "\n3. Technology: Level " << player.getHighestSkillLevel("technology")
    << "\n4. Navigation: Level " << player.getHighestSkillLevel("navigation") << endl;
    cout << "Which 2 skills would you like to use to navigate the hallway? (Enter one at a time, seperated by return characters)" << endl;
    int sk1, sk2;
    cin >> sk1 >> sk2;
    if((sk1==1 && sk2==2)||(sk2==1&&sk1==2)){
        if(player.getHighestSkillLevel("intelligence") + player.getHighestSkillLevel("instinct") > 13){
            cout << player.getHighestSkilled("intelligence").getFirstName() << " and " << player.getHighestSkilled("instinct").getFirstName() << " lead you through the hallway unharmed." << endl;
            return false;
        }else{
            cout << player.getLowestSkilled("technology").getFirstName() << " presses something they believe to be a door control. It floods the hallway with noxious gas." << endl;
            return true;
        }
    }else if((sk1==1 && sk2==3) || (sk2==1 && sk1==3)){
        if(player.getHighestSkillLevel("intelligence") + player.getHighestSkillLevel("technology") > 14){
            cout << player.getHighestSkilled("intelligence").getFirstName() << " and " << player.getHighestSkilled("technology").getFirstName() << " lead you through the hallway unharmed." << endl;
            return false;
        }else if(inventory.hasScanner() && player.getHighestSkillLevel("intelligence") + player.getHighestSkillLevel("technology") > 7 && player.getHighestSkillLevel("intelligence") + player.getHighestSkillLevel("technology") + 4 > 14){
            cout << player.getHighestSkilled("intelligence").getFirstName() << " and " << player.getHighestSkilled("technology").getFirstName() << " use the scanner to lead you through the hallway unharmed." << endl;
            return false;
        }else{
            cout << "You enter a sub-passage only to find yourself trapped with no way out." << endl;
            return true;
        }
    }else if((sk1==2 && sk2==4) || (sk2==2 && sk1==4)){
        if(player.getHighestSkillLevel("instinct") + player.getHighestSkillLevel("navigation") >  13){
            cout << player.getHighestSkilled("instinct").getFirstName() << " and " << player.getHighestSkilled("navigation").getFirstName() << " lead you through the hallway unharmed." << endl;
            return false;
        }else{
            cout << player.getLowestSkilled("instinct").getFirstName() << " opens a side door, which floods the hallway with water." << endl;
            return true;
        }
    }else{ // not a power combo
        int sum = 0;
        switch (sk1){
            case 1:
                sum+=player.getHighestSkillLevel("intelligence");
                break;
            case 2:
                sum+=player.getHighestSkillLevel("instinct");
                break;
            case 3:
                sum+=player.getHighestSkillLevel("technology");
                if(player.getHighestSkillLevel("technology")>5){
                    sum+=3;
                }
                break;
            case 4:
                sum+=player.getHighestSkillLevel("navigation");
                break;
            default:
                sum+=0;
        }
        switch (sk2){
            case 1:
                sum+=player.getHighestSkillLevel("intelligence");
                break;
            case 2:
                sum+=player.getHighestSkillLevel("instinct");
                break;
            case 3:
                sum+=player.getHighestSkillLevel("technology");
                if(player.getHighestSkillLevel("technology")>5){
                    sum+=3;
                }
                break;
            case 4:
                sum+=player.getHighestSkillLevel("navigation");
                break;
            default:
                sum+=0;
        }
        if(sum > 16){
            cout << "You make it through the hallway unharmed." << endl;
            return false;
        }else{
            cout << player.getLowestSkilled("intelligence").getFirstName() << " pokes something on a wall, which expands to consume their entire body. As the rest of the team attempts to free them, you all are consumed as well." << endl;
            return true;
        }
    }
}

bool activation(){
    cout << "You reach a chamber which contains a large quantity of high-level technology." << endl;
    while (true) {
        cout << "You can approach activating this technology one of two ways: \n1. Using Intelligence and Technology\n2. Using Instinct" << endl;
        int userChoice = 0;
        cin >> userChoice;
        switch (userChoice) {
            case 1:
                if (player.getHighestSkillLevel("intelligence") + player.getHighestSkillLevel("technology") > 13) {
                    cout << player.getHighestSkilled("intelligence").getFirstName() << " and " << player.getHighestSkilled("technology").getFirstName() << " successfully activate the technology."
                         << endl;
                    return false;
                } else {
                    cout << "You are unable to activate the technology" << endl;
                    return true;
                }
                break;
            case 2:
                if (player.getHighestSkillLevel("instinct") + (rand() % 10) > 13) {
                    cout << player.getHighestSkilled("instinct").getFirstName() << " is able to activate the technology." << endl;
                    return false;
                } else {
                    cout << "You are unable to activate the technology." << endl;
                    return true;
                }
                break;
            default:
                cout << "Invalid input" << endl;
        }
    }
}

bool pureOfSpirit(){
    cout << "The Secundum Principium has been activated! To pass through it, the spirit of each team member must be weighed. Only some will make it." << endl;
    for(int i=0; i<player.getTeamSlotsFilled(); i++){
        if(player.getTeamMember(i).getSkill("earnestness").getSkillLevel() > 6 || player.getTeamMember(i).getSkill("charisma").getSkillLevel() >9){
            cout << player.getTeamMember(i).getFirstName() << " makes it through!" << endl;
        }else{
            cout << player.getTeamMember(i).getFirstName() << " is instantly vaporized." << endl;
            player.removeTeamMember(player.getTeamMember(i));
            player.setTeamConf(player.getTeamConf()-10);
        }
    }
    if(player.getSkill("earnestness").getSkillLevel() > 6 || player.getSkill("charisma").getSkillLevel() > 9){
        cout << "You make it through!" << endl;
        return false;
    }else{
        cout << "You are instantly vaporized!" << endl;
        return true;
    }
}

bool secundumPrincipium(){
    cout << "You pass through the portal and emerge in a beautiful green forest." << endl;
    if(player.getTeamSlotsFilled() >= 2 && player.getTeamConf() >= 50){
        cout << "You and the remainder of your team start a happy new life on the planet, which you decide to name Terra." << endl;
        return false;
    }else if(player.getTeamSlotsFilled() >=1 && player.getTeamConf() >= 50){
        cout << "You and your one remaining team member start a happy new life on the planet, which you decide to name Terra." << endl;
        return false;
    }else if(player.getTeamSlotsFilled() == 0){
        cout << "You live out the rest of your days on the planet, which you name Terra." << endl;
        return false;
    }else if(player.getTeamConf() <=33){
        cout << "Your team starts a happy new life on the planet, which they decide to name Terra, but you are executed for being a terrible leader." << endl;
        return true;
    }else if(player.getTeamConf() <=50){
        cout << "You and the remainder of your team start a happy new life on the planet, which you decide to name Terra, but you are deposed as leader and replaced by " << player.getHighestSkilled("charisma").getFirstName() << "." << endl;
        return false;
    }else{
        return true; //don't think this can happen
    }
}

bool startModule() {
    bool gameover = false;
    switch (player.getProgress()) {
        case 0:
            gameover = manOverboard();
            break;
        case 1:
            gameover = raiders();
            break;
        case 2:
            gameover = witches();
            break;
        case 3:
            gameover = navigation();
            break;
        case 4:
            gameover = submersion();
            break;
        case 5:
            gameover = oneFalseStep();
            break;
        case 6:
            gameover = activation();
            break;
        case 7:
            gameover = pureOfSpirit();
            break;
        case 8:
            gameover = secundumPrincipium();
            break;

    }
    player.setProgress(player.getProgress() + 1);
    if (player.getTeamConf() <= 0) {
        return true;
    } else {
        return gameover;
    }
}

int main() {
    string firstNames[30] = {"Ayva", "Tyriq", "Abdulahi", "Carlo", "Violet", "Bessie", "Idris", "Mariyah", "Tianna", "Torin", "Charley", "Farhana", "Humera", "Lilith", "Carolyn", "Korban", "Dalia",
                             "Christos", "Alyx", "Madeline", "Tiegan", "Vlad", "Sia", "Sahara", "Graeme", "Blair", "Zachary", "Samual", "Jack", "Jannah"};
    string lastNames[30] = {"Avila", "Thornton", "Mathis", "Lister", "Joyner", "Santiago", "Bray", "Avalos", "Ortiz", "Carter", "Nash", "Dawson", "Shaw", "Rodriguez", "Salgado", "Schofield", "Le",
                            "Diaz", "Guest", "Campos", "Moss", "Humphries", "Haney", "Hassan", "Fletcher", "Southern", "Young", "Sheehan", "Bradford", "Hoffman"};
    string fName, lName;
    cout << "Welcome to The Quest For The Secundum Pricipium\n\n" << endl;
    cout << "What is your first name?" << endl;
    cin >> fName;
    cout << "What is your last name?" << endl;
    cin >> lName;
    player = User(fName, lName);
    inventory = Gear();
    cout << "Years ago, the ice caps on your planet melted, creating a flood that submerged all landmasses." << endl;
    cout << "You are part of a small group that has been living on a floatilla of boats ever since. However," << endl;
    cout << "there is an ancient legend which describes the \"Secundum Principium\": a gateway to a new and" << endl;
    cout << "pure world, where you could start your species anew.\n" << endl;
    cout << "The leader of your community has tasked you with leading a team of your choice on a quest to find" << endl;
    cout << "the Secundum Principium. Each member of the community has different skills which will help you on" << endl;
    cout << "your journey, so choose your team members carefully. You also have 12 inventory slots to fill. Each" << endl;
    cout << "item has properties that will help you on your journey." << endl;

    string userIn = "n";
    while (userIn != "y") {
        cout << "Are you ready to pick your team? (y/n)" << endl;
        cin >> userIn;
    }

    //generate team members
    cout << "The members of your community are:" << endl;
    cout << "\nYou: " << player.format() << endl;
    TeamMember community[12];
    for (int i = 0; i < 12; i++) {
        community[i] = TeamMember(firstNames[rand() % 30], lastNames[rand() % 30]);
//        cout << i + 1 << ": " << community[i].format() << endl;
    }
    string str = "";
    int numPerRow = 6;
    printTeam(numPerRow, community);
    int numChoice = 0;
    vector<int> prevChosen;
    while (player.getTeamSlotsFilled() < 6) {
        cout << "There are " << 6 - player.getTeamSlotsFilled() << " seats remaining on your boat." << endl;
        cout << "Who is your choice? (Enter the number of the community member you would like to add to your team)" << endl;
        cin >> numChoice;
        bool inGood = numChoice > 0 && numChoice <= 12;
        for (int i : prevChosen) {
            inGood = inGood && (i != numChoice);
        }
        if (inGood) {
            player.addTeamMember(community[numChoice - 1]);
            prevChosen.push_back(numChoice);
            cout << community[numChoice - 1].getFirstName() << " " << community[numChoice - 1].getLastName() << " added!" << endl;
        } else {
            cout << "Invalid format." << endl;
        }
    }

    cout << "\nCongrats! Your team has been created." << endl;
    cout << "To supplement the skills of your team, you have 12 inventory slots to fill with any combination of the following items: " << endl;
    cout << "1. Medical Kit\n2. Weapons\n3. Tradeable Goods\n4. Star Chart\n5. Diving Gear\n6. Scanner" << endl;
    cout << "\nWhile all these items will help you in your journey, some \"boost\" certain skills:" << endl;
    cout << "Medical Kit boosts Medical\nTradeable Goods boosts Bartering\nWeapons boosts Combat\nStar Chart boosts Navigation\nScanner boosts Technology" << endl;
    cout << "\nAdditionally, you may only include one Star Chart and Scanner. All other items may be duplicated, and may be used up during your quest." << endl;
    string addMore = "y";
    while (inventory.getSlotsFilled() < 12 && addMore != "n") {
        cout << inventory.format() << endl;
        cout << "You have " << 12 - inventory.getSlotsFilled() << " slots remaining." << endl;
        cout << "Would you like to add an item? (y/n)" << endl;
        cin >> addMore;
        if (addMore == "y") {
            cout << "What item would you like to add?" << endl;
            cout << "1. Medical Kit\n2. Weapons\n3. Tradeable Goods\n4. Star Chart\n5. Diving Gear\n6. Scanner" << endl;
            cin >> numChoice;
            if (numChoice > 0 && numChoice <= 6) {
                if (numChoice == 1) {
                    inventory.fillSlot("medicalKit");
                } else if (numChoice == 2) {
                    inventory.fillSlot("weapons");
                } else if (numChoice == 3) {
                    inventory.fillSlot("tradeableGoods");
                } else if (numChoice == 4 && !inventory.hasStarChart()) {
                    inventory.fillSlot("starChart");
                } else if (numChoice == 5) {
                    inventory.fillSlot("divingGear");
                } else if (numChoice == 6 && !inventory.hasScanner()) {
                    inventory.fillSlot("scanner");
                } else {
                    cout << "Invalid selection." << endl;
                }
            } else {
                cout << "Invalid input." << endl;
            }
        }
    }

    cout << "\n\nCongrats! You are ready to begin your quest." << endl;

    int mainMenuChoice = 0;
    int teamChoice = 0;
    int skillChoice = 0;
    int tradeChoice = 0;
    string modNames[9] = {"Man Overboard", "Raiders", "Witches", "Navigation", "Submersion", "One False Step", "Activation", "Pure of Spirit", "Secundum Principium"};
    bool gameLost = false;
    while (mainMenuChoice != 7 && !gameLost && player.getProgress() < 9) {
        cout << "Module " << player.getProgress() + 1 << ": " << modNames[player.getProgress()] << "\n" << endl;
        cout << "Team members: " << player.getTeamSlotsFilled() << "  |  Inventory Filled: " << inventory.getSlotsFilled() << "  |  Team Confidence: " << player.getTeamConf() << endl;
        cout << "---------------\nMain Menu\n---------------" << endl;
        cout << "1. Begin Module\n2. View Team\n3. View Gear\n4. Learn Skills\n5. Attempt Trade\n6. Help\n7. Quit" << endl;
        cin >> mainMenuChoice;
        switch (mainMenuChoice) {
            case 1:
                gameLost = startModule();
                break;
            case 2:
                while (teamChoice != player.getTeamSlotsFilled() + 2) {
                    cout << "---------------\nView Team Stats\n---------------" << endl;
                    cout << "1. " << player.getFirstName() << " " << player.getLastName() << " (you)" << endl;
                    for (int i = 0; i < player.getTeamSlotsFilled(); i++) {
                        cout << i + 2 << ". " << player.getTeamMember(i).getFirstName() << " " << player.getTeamMember(i).getLastName() << endl;
                    }
                    cout << player.getTeamSlotsFilled() + 2 << ". Return to main menu" << endl;
                    cin >> teamChoice;
                    if (teamChoice == 1) {
                        cout << player.format() << endl;
                    } else if (teamChoice > 1 && teamChoice < player.getTeamSlotsFilled() + 2) {
                        cout << player.getTeamMember(teamChoice - 2).format();
                    } else if (teamChoice == player.getTeamSlotsFilled() + 2) {
                        //do nothing
                    } else {
                        cout << "Invalid input" << endl;
                    }
                }
                break;
            case 3:
                cout << inventory.format() << endl;
                break;
            case 4:
                cout << "By learning a skill, you will replace your current level of that skill with a random value.\nYour current skills are: " << endl;
                cout << player.format() << endl;
                cout << "Select a skill to learn: " << endl;
                cout
                        << "1. Strength\n2. Dexterity\n3. Intelligence\n4. Instinct\n5. Charisma\n6. Swimming\n7. Medical\n8. Technology\n9. Bartering\n10. Combat\n11. Navigation\n12. Earnestness\n 13. Cancel"
                        << endl;
                cin >> skillChoice;
                switch (skillChoice) {
                    case 1:
                        player.updateSkill(Skill("strength", rand() % 11));
                        break;
                    case 2:
                        player.updateSkill(Skill("dexterity", rand() % 11));
                        break;
                    case 3:
                        player.updateSkill(Skill("intelligence", rand() % 11));
                        break;
                    case 4:
                        player.updateSkill(Skill("instinct", rand() % 11));
                        break;
                    case 5:
                        player.updateSkill(Skill("charisma", rand() % 11));
                        break;
                    case 6:
                        player.updateSkill(Skill("swimming", rand() % 11));
                        break;
                    case 7:
                        player.updateSkill(Skill("medical", rand() % 11));
                        break;
                    case 8:
                        player.updateSkill(Skill("technology", rand() % 11));
                        break;
                    case 9:
                        player.updateSkill(Skill("bartering", rand() % 11));
                        break;
                    case 10:
                        player.updateSkill(Skill("combat", rand() % 11));
                        break;
                    case 11:
                        player.updateSkill(Skill("navigation", rand() % 11));
                        break;
                    case 12:
                        player.updateSkill(Skill("earnestness", rand() % 11));
                        break;
                    case 13:
                        // do nothing
                        break;
                    default:
                        cout << "Invalid input" << endl;
                        break;
                }
                cout << "New skill list: \n" << player.format() << endl;
                break;
            case 5:
                if ((rand() % 50 - player.getProgress()) >= 25) {
                    cout << "You have found a group of wandering traders! They will accept Tradeable Goods in exchange for a variety of items." << endl;
                    cout << "\nCurrent " << inventory.format() << endl;
                    cout << "\nYou have " << inventory.countItems("tradeableGoods") << " Tradeable Goods and " << 12 - inventory.getSlotsFilled() << " inventory slots open." << endl;
                    if (inventory.countItems("tradeableGoods") > 0) {
                        while (inventory.countItems("tradeableGoods") > 0 && tradeChoice != 6) {
                            cout << "Which item would you like to trade for?" << endl;
                            cout << "1. Medical Kit\n2. Weapons\n3. Star Chart\n4. Diving Gear\n5. Scanner\n6. Cancel" << endl;
                            cin >> tradeChoice;
                            if (tradeChoice == 3 && inventory.hasStarChart()) {
                                cout << "You can only have one star chart" << endl;
                            } else if (tradeChoice == 5 && inventory.hasScanner()) {
                                cout << "You can only have one scanner" << endl;
                            } else {
                                inventory.useItem("tradeableGoods");
                                switch (tradeChoice) {
                                    case 1:
                                        inventory.fillSlot("medicalKit");
                                        cout << "Medical Kit added!" << endl;
                                        break;
                                    case 2:
                                        inventory.fillSlot("weapons");
                                        cout << "Weapons added!" << endl;
                                        break;
                                    case 3:
                                        inventory.fillSlot("starChart");
                                        cout << "Star Chart added!" << endl;
                                        break;
                                    case 4:
                                        inventory.fillSlot("divingGear");
                                        cout << "Diving Gear added!" << endl;
                                        break;
                                    case 5:
                                        inventory.fillSlot("scanner");
                                        cout << "Scanner added!" << endl;
                                        break;
                                    case 6:
                                        //do nothing
                                        break;
                                    default:
                                        cout << "Invalid input" << endl;
                                }
                            }
                        }

                    } else {
                        cout << "You have no goods to trade." << endl;
                    }
                } else {
                    cout << "You could not find anyone to trade with." << endl;
                }
                break;
            case 6:
                //TODO add gameplay instructions
                break;
            case 7:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid input." << endl;
        }
    }

    int score = player.getProgress();
    if(player.getProgress()==9){
        score += player.getTeamConf();
    }
    ifstream file;
    file.open("../highScore.txt");
    string highScorer;
    string highScore;
    if(file.is_open()){
        getline(file, highScorer);
        getline(file, highScore);
    }
    file.close();
    if(gameLost){
        cout << "YOU LOSE"<< endl;
    }else if(player.getProgress()==9 && mainMenuChoice != 7){
        cout << "YOU WIN" << endl;
    }
    cout << "Your score was: " << score << endl;
    cout << "The high score is: " << highScore << endl;
    if(score >= stoi(highScore)){
        cout << "You've beat the high score!" << endl;
        ofstream fileW;
        fileW.open("../highScore.txt", ofstream::out | ofstream::trunc);
        fileW << player.getFirstName() << " " << player.getLastName() << "\n";
        fileW << score << "\n";
        fileW.close();
    }

    return 0;
}
