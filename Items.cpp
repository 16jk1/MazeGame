#include <iostream>
#include <string>
#include "Item.h"

using namespace std;

//Getter methods
int Item::getItemXPos() const {
    return x;
}

int Item::getItemYPos() const {
    return x;
}

int Item::getItemScarcity() const {
    return x;
}

string Item::getItemColor() const {
    return color;
}

bool Item::isActivated() const{
    return activated;
}
//int Item::ability() {
//    return
//}

// Items
Item::Item(){
    x = 0;
    y = 0;
    color = "blue";
    itemScarcity = 5;
    activated = false;
}

Item::Item(const string& ability){
    //int abiiltyType = rand() % 4;
    // Change to end locations on the maze but 0's for now
    x = 0;
    y = 0;
    if (ability == "boots"){
        // Incorporate player movement
        // Blue glowing tint
        color = "blue";
        itemScarcity = 10;
        activated = false;
    }
//    }else if (ability == "dynamite"){
//        // Same incorporation
//    }else if (ability == "spikes"){
//        // Same incorporation
//    }else if (ability == "spiderWeb"){
//        // Same incorporation
//    }
}

// Destructor
Item::~Item(){

}
