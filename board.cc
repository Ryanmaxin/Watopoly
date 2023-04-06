#include "board.h"
#include "player.h"
#include "memory"
#include "unownableproperty.h"
#include "ownableproperty.h"
#include "gym.h"
#include "residence.h"
#include "academicbuilding.h"
#include "enumerations.h"

#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::unique_ptr;
using std::make_unique;
using std::pair;
using std::cout;
using std::endl;

void Board::init(string square_data) {
    //Clear previous state.
    squares.clear();

    //Initialize squares
    //... Some code here

}

Square* Board::getSquare(int index) {
    return squares[index].get();
}

//Might not be necessary
// Square* Board::stringToProperty(string property) {
//     for (size_t i; i < 40; ++i) {
//         if (locations[i]->getName() == property) {
//             return locations[i].get();
//         }
//     }
//     //If no property found
//     return nullptr;
// }

void Board::initSquares() {
    

    
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<AcademicBuilding>("AL",Monopoly::Arts1));
    // locations.push_back(make_unique<UnownableProperty>("SLC"));
    // locations.push_back(make_unique<AcademicBuilding>("ML",Monopoly::Arts1));
    // locations.push_back(make_unique<UnownableProperty>(""));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
    // locations.push_back(make_unique<UnownableProperty>("COLLECT OSAP"));
}
