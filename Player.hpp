#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <iostream>
#include "Property.hpp"

class Property;
class Player {
private:
    std::string name;
    std::vector<Property*> ownedProperties;
public:
    Player(const std::string& name);
    std::vector<Property*> getOwnedProperties();
    const std::string& getName() const;
    void addProperty(Property* property);
    int money;
    int position;
    int trainsOwned;
    int outOfJailCard;
    bool isBankrupt;
    bool isJailed;
    bool removeGetOutOfJailCard();
    void pay(int amount);
};

#endif // PLAYER_H
