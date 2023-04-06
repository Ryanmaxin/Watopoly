#include "ownableproperty.h"
#include "square.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

OwnableProperty::OwnableProperty(string n, int p):
Square{n}, owner{nullptr},price{p} {}

Player* OwnableProperty::getOwner() {
    return owner;
}
void OwnableProperty::setOwner(Player* new_owner) {
    owner = new_owner;
}
int OwnableProperty::getPrice() {
    return price;
}


