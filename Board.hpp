#ifndef BOARD_H
#define BOARD_H

#include "Property.hpp"
#include <vector>

// Define a structure for color groups
class Street;
struct ColorGroup {
    std::string name;
    std::vector<Street*> streets; // Stores streets belonging to this color group
};

class Board {
private:
    std::vector<Property*> Propertys; // Vector to hold pointers to Property objects
    std::vector<ColorGroup> colorGroups; // Stores color groups
    int jailIndex;
    int IllinoisAveIndex;
    int CharlesPlaceIndex;
    int BoardWalkIndex;

public:
    Board();
    ~Board(); // Destructor to clean up dynamically allocated Propertys

    void addProperty(Property* Property); // Add a Property to the board
    Property* getProperty(unsigned int index) const; // Get a Property by index
    int getNumberOfPropertys() const; // Get the total number of Propertys
    int getJailIndex();
    int getIllinoisAveIndex();
    int getCharlesPlaceIndex();
    int getBoardWalkIndex();
    int getNearestUtilityIndex(int startPosition);
    int getNearestRailroadIndex(int startPosition);
    void initializeColorGroups(); // Initialize color groups and add streets
    std::vector<ColorGroup>& getColorGroups();
};

#endif // BOARD_H
