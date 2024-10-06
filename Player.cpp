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

void Player::updatePositions(int board, int space){
    //check corners
    if(position == 0){
        positionX = board - space;
        positionY = board - space;
    } else if(position == 10){
        positionX = space/3*2;
        positionY = board - space;
    } else if(position == 19){
        positionX = space/3*2;
        positionY = space;
    } else if(position == 29){
        positionX = board - space;
        positionY = space/3*2;
    }
    
    //check sides
    if (position > 0 && position <= 9) {
        positionX = board - (position * space + space);
        positionY = board - space;
    } else if (position > 10 && position <= 18) {
        positionX = space/2;
        positionY = board - ((position - 10) * space + space);
    } else if (position > 19 && position <= 28) {
        positionX = (28 - position) * space + space;
        positionY = space/2;
    } else if (position > 29 && position <= 37) {
        positionX = board - space;
        positionY = (position - 29) * space + space;
    }
}