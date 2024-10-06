#include "Property.hpp"
#include "Player.hpp"
#include "Game.hpp"
Property::Property(const std::string& name, bool isUtility, bool isRailroad)
    : name(name), owner(nullptr), owned(false), isUtility(isUtility), isRailroad(isRailroad), houseCount(0), hotelCount(0) {}

const std::string& Property::getName() const {
    return name;
}

void Property::setOwner(Player* newOwner) {
    owner = newOwner;
    if(newOwner != nullptr){
        owned = true;
    } else {
        owned = false;
    }
}
Player* Property::getOwner(){
    return owner;
}

SpecialProperty::SpecialProperty(const std::string& name, Game* game, SpecialAction action): Property(name, false, false), game(game), action(action) {}

void SpecialProperty::landOn(Player& player){
    if(action == SpecialAction::Chance){
        executeAction(player, SpecialAction(rand() % 16));
    } else {
        executeAction(player, action);
    }
}

void SpecialProperty::executeAction(Player& player, SpecialAction action) {
    switch (action) {
        case SpecialAction::Chance:
            //unreachable
            break;
        case SpecialAction::Jail:
            if(!player.removeGetOutOfJailCard())
                player.isJailed = true;
            break;
        case SpecialAction::FreeParking:
            std::cout << player.getName() << " is parking for free." << std::endl;
            break;
        case SpecialAction::AdvanceToGo:
            player.money += 200;
            player.position = 0; // Assuming Go is at index 0
            std::cout << player.getName() << " advances to Go and collected $200!" << std::endl;
            break;

        case SpecialAction::BankDividend:
            player.money += 50;
            std::cout << player.getName() << " receives a dividend of $50!" << std::endl;
            break;

        case SpecialAction::GoBack3Spaces:
            {
                int currentPosition = player.position;
                player.position = currentPosition - 3;
                std::cout << player.getName() << " goes back 3 spaces!" << std::endl;
                game->board.getProperty(player.position)->landOn(player); //reland on the new Property
            }
            break;

        case SpecialAction::GoToJail:
            if(!player.removeGetOutOfJailCard()){
                player.isJailed = true;
                player.position = game->board.getJailIndex();
                std::cout << player.getName() << " goes directly to Jail!" << std::endl;
            } else {
                std::cout << player.getName() << " skipped jail time!" << std::endl;
            }
            break;

        case SpecialAction::GeneralRepairs:
            {
                int totalCost = 0;
                for (const auto& street : player.getOwnedProperties()) {
                    totalCost += (street->houseCount * 25) + (street->hotelCount * 100);
                }
                player.pay(totalCost);
                std::cout << player.getName() << " pays $" << totalCost << " for repairs!" << std::endl;
            }
            break;

        case SpecialAction::PoorTax:
            player.pay(15);
            std::cout << player.getName() << " pays a poor tax of $15!" << std::endl;
            break;

        case SpecialAction::TripToReadingRailroad:
            player.position = 5;
            if (player.position == 0) {
                player.money += 200;
                std::cout << player.getName() << " passes Go and collects $200!" << std::endl;
            }
            std::cout << player.getName() << " takes a trip to Reading Railroad!" << std::endl;
            break;

        case SpecialAction::WalkOnBoardwalk:
            if (player.position > game->board.getBoardWalkIndex()) {
                player.money += 200;
                std::cout << player.getName()  << " has passed the GO point and received $200" << std::endl;
            }
            player.position = game->board.getBoardWalkIndex();
            std::cout << player.getName() << " advances to game->boardwalk!" << std::endl;
            break;

        case SpecialAction::ElectedChairman:
            for (auto& otherPlayer : game->getPlayers()) {
                if (otherPlayer.getName() != player.getName()) {
                    otherPlayer.pay(50);
                    player.money += 50;
                }
            }
            std::cout << player.getName() << " paid each player $50!" << std::endl;
            break;

        case SpecialAction::LoanMaturity:
            player.money += 150;
            std::cout << player.getName() << " collected $150 from matured loan!" << std::endl;
            break;

        case SpecialAction::GetOutOfJailFree:
            player.outOfJailCard++;
            std::cout << player.getName() << " received a Get Out of Jail Free card!" << std::endl;
            break;

        case SpecialAction::AdvanceToIllinois:
            if (player.position > game->board.getIllinoisAveIndex()) {
                player.money += 200;
                std::cout << player.getName()  << " has passed the GO point and received $200" << std::endl;
            }
            player.position = game->board.getIllinoisAveIndex();
            break;

        case SpecialAction::AdvanceToStCharles:
            if (player.position > game->board.getCharlesPlaceIndex()) {
                player.money += 200;
                std::cout << player.getName()  << " has passed the GO point and received $200" << std::endl;
            }
            player.position = game->board.getCharlesPlaceIndex();
            break;

        case SpecialAction::AssessStreetRepairs:
            {
                int totalCost = 0;
                for (const auto& street : player.getOwnedProperties()) {
                    totalCost += (street->houseCount * 40) + (street->hotelCount * 115);
                }
                player.pay(totalCost);
                std::cout << player.getName() << " pays $" << totalCost << " for street repairs!" << std::endl;
            }
            break;

        case SpecialAction::AdvanceToNearestUtility:
            {
                // Implement logic for advancing to nearest utility
                int currentPosition = player.position;
                player.position = game->board.getNearestUtilityIndex(player.position);
                if(currentPosition > player.position){
                    player.money += 200;
                    std::cout << player.getName()  << " has passed the GO point and received $200" << std::endl;
                }
            }
            break;
        case SpecialAction::AdvanceToNearestRailroad:
            {
                    // Implement logic for advancing to nearest utility
                int currentPosition = player.position;
                player.position = game->board.getNearestRailroadIndex(player.position);
                if(currentPosition > player.position){
                    player.money += 200;
                    std::cout << player.getName()  << " has passed the GO point and received $200" << std::endl;
                }
            }
            break;
        case SpecialAction::ElectricCompany:
            player.pay(150);
            std::cout << player.getName() << " pays a electric bill of $150!" << std::endl;
            break;
        case SpecialAction::WaterWorks:
            player.pay(150);
            std::cout << player.getName() << " pays a water bill of $150!" << std::endl;
            break;
        case SpecialAction::LuxuryTax:
            player.pay(100);
            std::cout << player.getName() << " pays a luxury tax of $100!" << std::endl;
            break;
        case SpecialAction::CommunityChest:
            int random = rand() % 100;
            player.money += random;
            std::cout << player.getName() << " found $" << random << " in community chest!" << std::endl;
            break;        
    }
}

Street::Street(const std::string& name, int price, int rent, int housePrice, int hotelPrice, struct ColorGroup& colorGroup)
    : Property(name, true, false), colorGroup(colorGroup), price(price), rent(rent), housePrice(housePrice), hotelPrice(hotelPrice){
        colorGroup.streets.push_back(this);
    }

void Street::landOn(Player& player) {
    if (!owned) {
        // Handle property purchase logic
        std::cout << player.getName() << " landed on " << getName() << "." << std::endl;
        // Logic to allow player to buy the property
        std::cout << "Would you like to purchase " << getName() << " for " << price << "? (y/n)" << std::endl;
        std::string input;
        std::cin >> input;
        if(input == "y"){
            if(player.money >= price){
                player.pay(price);
                setOwner(&player);
                player.addProperty(this);
            } else {
                std::cerr << player.getName() << " can't afford this Property!" << std::endl;
            }
        } else if(input != "n"){
            std::cerr << "Unknown input, skipping...." << std::endl;
        }
    } else {
        // Handle rent payment / build house logic
        if(player.getName() != owner->getName()){
            std::cout << player.getName() << " landed on " << getName() << " and has to pay rent to " << owner->getName() << "." << std::endl;
            int totalRent = calculateRent();
            player.pay(totalRent);
            owner->money += totalRent;
            std::cout << player.getName() << " paid " << totalRent << " in rent to " << owner->getName() << "." << std::endl;
        } else {
            std::cout << player.getName() << " owns the current street." << std::endl;
            for(unsigned int i = 0; i < colorGroup.streets.size(); i++){
                if(colorGroup.streets[i]->owner->getName() != player.getName()){
                    std::cout << player.getName() << " doesn't own the entire color group, he can't build a house here." << std::endl;
                    return;
                }
            }
            std::cout << player.getName() << " owns the entire color group, he can build a house here." << std::endl;
            buildHouse(player);
        }
    }
}

// Logic to build a house on this street
void Street::buildHouse(Player& player) {
    if(houseCount == 4){
        std::cerr << "Would you like to upgrade the houses to a hotel?" << std::endl;
        std::string input;
        std::cin >> input;
        if(input == "y"){
            if(player.money >= hotelPrice){
                player.pay(hotelPrice);
                houseCount = 0;
                hotelCount++;
            } else {
                std::cerr << player.getName() << " can't afford this Property!" << std::endl;
            }
        } else if(input != "n"){
            std::cerr << "Unknown input, skipping...." << std::endl;
        }
    } else {
        std::cout << "Would you like to purchase a house on property " << getName() << "? (y/n)" << std::endl;
        std::string input;
        std::cin >> input;
        if(input == "y"){
            if(player.money >= housePrice){
                player.pay(housePrice);
                houseCount++;
            } else {
                std::cerr << player.getName() << " can't afford this Property!" << std::endl;
            }
        } else if(input != "n"){
            std::cerr << "Unknown input, skipping...." << std::endl;
        }
    }
}

int Street::calculateRent() const {
    int rental = rent;
    for(int i = 0; i < houseCount; i++){
        rental *= 2;
    }
    for(int i = 0; i < hotelCount; i++){
        rental *= 16;
    }
    return rental;
}

Train::Train(const std::string& name, int cost, int taxPerTrain)
    : Property(name, false, true), cost(cost), taxPerTrain(taxPerTrain) {}

void Train::landOn(Player& player) {
    if (!owned) {
        // Logic for purchasing the train
        std::cout << player.getName() << " landed on " << getName() << " and can purchase it for " << cost << "." << std::endl;
        // Logic to allow player to buy the property
        std::cout << "Would you like to purchase " << getName() << "? (y/n)" << std::endl;
        std::string input;
        std::cin >> input;
        if(input == "y"){
            if(player.money >= cost){
                player.pay(cost);
                setOwner(&player);
                player.addProperty(this);
                player.trainsOwned++;
            } else {
                std::cerr << player.getName() << " can't afford this Property!" << std::endl;
            }
        } else if(!(input == "n")){
            std::cerr << "Unknown input, skipping...." << std::endl;
        }
    } else {
        // Logic for paying tax based on number of trains owned by the owner
        if(owner->getName() != player.getName()){
            int ownerTrainCount = owner->trainsOwned;
            int totalTax = ownerTrainCount * taxPerTrain;
            player.pay(totalTax);
            owner->money += totalTax;
            std::cout << player.getName() << " paid " << totalTax << " in tax to " << owner->getName() << "." << std::endl;
        } else {
            std::cout << player.getName() << " owns the current train." << std::endl;
        }
    }
}