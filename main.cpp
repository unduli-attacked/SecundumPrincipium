#include <iostream>
#include "TeamMember.h"
#include "User.h"
#include <iomanip>

using namespace std;

void startModule(int modNum) {
    switch (modNum) {

    }
}

void printTeam(string teamList[], int numMembers) {

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
    User player = User(fName, lName);
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
        for(int k=0; k <12; k++){
            for(int j=0; j<numPerRow; j++) {
                str = community[i+j].getSkill(k).getSkillName() + ": " + to_string(community[i+j].getSkill(k).getSkillLevel());
                cout << left << setw(22) << str;
            }
            cout << endl;
        }
        cout << endl;
    }
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
    while (player.getGear().getSlotsFilled() < 12 && userIn != "n") {
        cout << player.getGear().format() << endl;
        cout << "You have " << 12 - player.getGear().getSlotsFilled() << " slots remaining." << endl;
        cout << "Would you like to add an item? (y/n)" << endl;
        cin >> userIn;
        if(userIn=="y") {
            cout << "What item would you like to add?" << endl;
            cin >> numChoice;
            if (numChoice > 0 && numChoice <= 6) {
                if (numChoice == 1) {
                    player.addGearItem("medicalKit");
                } else if (numChoice == 2) {
                    player.addGearItem("weapons");
                } else if (numChoice == 3) {
                    player.addGearItem("tradeableGoods");
                } else if (numChoice == 4 && !player.getGear().hasStarChart()) {
                    player.addGearItem("starChart");
                } else if (numChoice == 5) {
                    player.addGearItem("divingGear");
                } else if (numChoice == 6 && !player.getGear().hasScanner()) {
                    player.addGearItem("scanner");
                } else {
                    cout << "Invalid selection." << endl;
                }
            } else {
                cout << "Invalid input." << endl;
            }
        }
    }

    cout << "\n\nCongrats! You are ready to begin your quest.\n\n\n" << endl;

    int mainMenuChoice = 0;
    string modName = "Man Overboard";
    while (mainMenuChoice != 7) {
        cout << "Module " << player.getProgress() + 1 << ": " << modName << "\n" << endl;
        cout << "Team members: " << player.getTeamSlotsFilled() << "  |  Inventory Filled: " << player.getGear().getSlotsFilled() << "  |  Team Confidence: " << player.getTeamConf() << endl;
        cout << "---------------\nMain Menu\n---------------" << endl;
        cout << "1. Begin Module\n2. View Team\n3. View Gear\n4. Learn Skills\n5. Attempt Trade\n6. Help\n7. Quit" << endl;
        cin >> mainMenuChoice;
        switch (mainMenuChoice) {
            case 1:
                startModule(player.getProgress());
                break;
            case 2:

            case 3:

            case 4:

            case 5:

            case 6:

            case 7:
                cout << "Goodbye!" << endl;
                break;
            default:
                cout << "Invalid input." << endl;
        }
    }

    return 0;
}
