#include "Player.hpp"
Player::Player(const std::string& name)
    : name(name), money(1500), position(0), trainsOwned(0),outOfJailCard(0), isBankrupt(false), isJailed(false) {}

void Player::pay(int amount) {
    if(money - amount < 0){
        std::cout << getName() << " has declared bankruptcy" << std::endl;
        isBankrupt = true;
        for(auto& property: ownedProperties){
            property->setOwner(nullptr);
            property->houseCount = 0;
            property->hotelCount = 0;
        }
    }
    money -= amount;
}

const std::string& Player::getName() const {
    return name;
}

void Player::addProperty(Property* property) {
    if (property) {
        ownedProperties.push_back(property);
        if (property->isRailroad) {
            trainsOwned++;
        }
    }
}

std::vector<Property*> Player::getOwnedProperties(){
    return ownedProperties;
}

bool Player::removeGetOutOfJailCard(){
    if(outOfJailCard > 0){
        outOfJailCard--;
        return true;
    }
    return false;
}