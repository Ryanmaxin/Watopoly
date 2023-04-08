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
#include <fstream>
#include <sstream>

using std::vector;
using std::string;
using std::unique_ptr;
using std::make_unique;
using std::pair;
using std::cout;
using std::endl;
using std::ifstream;
using std::istringstream;

void Board::init(string square_data) {
    //Clear previous state.
    squares.clear();

    //Initialize squares
    //... Some code here

}

Square* Board::getSquare(int index) {
    return squares[index].get();
}

Square* Board::stringToProperty(string property) {
    for (size_t i = 0; i < 40; ++i) {
        if (squares[i]->getName() == property) {
            return squares[i].get();
        }
    }
    //If no property found
    return nullptr;
}

void Board::initSquares(string square_data) {
    ifstream f { square_data };
    string s;
    for (int i = 0; i < 40; ++i) {
        string line = getline(f,s);
        istringstream iss {line};
        string token;
        bool is_first = true;
        string type;
        
        iss >> type;
        if (type == "u") {
            string name, new_token;
            while (iss >> new_token) {
                name += new_token
            }
            squares.push_back(make_unique<UnownableProperty>(name));
        }
        } else if (type == "a") {
            string name;
            int price, imp_cost;
            Monopoly set;
            vector<int> rent_vector;

            iss >> name;
            iss >> set;
            iss >> price;
            iss >> imp_cost;
            
            for (int i = 0; i < 6; i++) {
                int theRent;
                iss >> theRent;
                rent_vector.push_back(theRent)
            }
            squares.push_back(make_unique<AcademicBuilding>(name, price, set, rent_vector, imp_cost));
        } else if (type == "g") {
            string name;
            int price;
            iss >> name;
            iss > price;
            squares.push_back(make_unique<Gym>(name, price));
        } else if (type == "r") {
            string name;
            int price;
            iss >> name;
            iss > price;
            squares.push_back(make_unique<Residence>(name, price));
        }

    squares.push_back(make_unique<UnownableProperty>);
}

Monopoly Board::stringToMonopoly(string monopoly) {
    if (monopoly == "Arts1") return Monopoly::Arts1;
    else if (monopoly == "Arts2") return Monopoly::Arts2;
    else if (monopoly == "Eng") return Monopoly::Eng;
    else if (monopoly == "Health") return Monopoly::Health;
    else if (monopoly == "Env") return Monopoly::Env;
    else if (monopoly == "Sci1") return Monopoly::Sci1;
    else if (monopoly == "Sci2") return Monopoly::Sci2;
    else return Monopoly::Math;
}
