#include <iostream>
#include "Board.hpp"

// Constructor to initialize the board
Board::Board():jailIndex(-1), IllinoisAveIndex(-1), CharlesPlaceIndex(-1),BoardWalkIndex(-1){
    colorGroups.push_back({"Brown", {}});
    colorGroups.push_back({"Light Blue", {}});
    colorGroups.push_back({"Pink", {}});
    colorGroups.push_back({"Orange", {}});
    colorGroups.push_back({"Red", {}});
    colorGroups.push_back({"Yellow", {}});
    colorGroups.push_back({"Green", {}});
    colorGroups.push_back({"Dark Blue", {}});
}

// Destructor to clean up dynamically allocated Propertys
Board::~Board() {
    for (auto Property : Propertys)
        delete Property;
}

// Add a new Property to the board
void Board::addProperty(Property* Property) {
    if(Property->getName() == "JAIL"){
        jailIndex = Propertys.size();
    } else if(IllinoisAveIndex == -1){
        if(Property->getName() == "ILLINOIS AVENUE"){
            IllinoisAveIndex = Propertys.size();
        }
    } else if(CharlesPlaceIndex == -1){
        if(Property->getName() == "ST.CHARLES PLACE"){
            CharlesPlaceIndex = Propertys.size();
        }
    } else if(CharlesPlaceIndex == -1){
        if(Property->getName() == "BOARDWALK"){
            BoardWalkIndex = Propertys.size();
        }
    } else if(CharlesPlaceIndex == -1){
        if(Property->getName() == "ST.CHARLES PLACE"){
            CharlesPlaceIndex = Propertys.size();
        }
    }
    //
    Propertys.push_back(Property);
}

// Get a Property by index
Property* Board::getProperty(unsigned int index) const {
    if (index >= 0 && index < Propertys.size()) {
        return Propertys[index];
    }
    return nullptr; // Return nullptr for invalid index
}

// Get the total number of Propertys
int Board::getNumberOfPropertys() const {
    return Propertys.size();
}

int Board::getJailIndex(){
    return jailIndex;
}

int Board::getIllinoisAveIndex(){
    if(IllinoisAveIndex == -1){
        std::cerr << "Error: Illinois Aven doesn't exist, advancing to go" << std::endl;
        return 0;
    }
    return IllinoisAveIndex;
}

int Board::getCharlesPlaceIndex(){
    if(CharlesPlaceIndex == -1){
        std::cerr << "Error: ST.CHARLES PLACE doesn't exist, advancing to go" << std::endl;
        return 0;
    }
    return CharlesPlaceIndex;
}

int Board::getBoardWalkIndex(){
    if(BoardWalkIndex == -1){
        std::cerr << "Error: ST.CHARLES PLACE doesn't exist, advancing to go" << std::endl;
        return 0;
    }
    return BoardWalkIndex;
}

int Board::getNearestUtilityIndex(int startPosition){
    for(int i = startPosition + 1; i != startPosition; i = (i + 1 ) % Propertys.size()){
        if(Propertys[i]->isUtility){
            return i;
        }
    }
    std::cerr << "Error: No ulitily found." << std::endl;
    return 0;
}

int Board::getNearestRailroadIndex(int startPosition){
    for(int i = startPosition+1; i != startPosition; i = (i + 1 ) % Propertys.size()){
        if(Propertys[i]->isRailroad){
            return i;
        }
    }
    std::cerr << "Error: No railroad found." << std::endl;
    return 0;
}

std::vector<ColorGroup>& Board::getColorGroups(){
    return colorGroups;
}