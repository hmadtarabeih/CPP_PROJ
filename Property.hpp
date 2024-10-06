#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
#include <iostream>
class Player;
class Game;
class Property {
protected:
    std::string name;
    Player* owner; // Pointer to the owning player

public:
    Property(const std::string& name, bool isUtility, bool isRailroad);
    virtual ~Property() = default;
    virtual void landOn(Player& player) = 0; // Pure virtual function
    const std::string& getName() const;
    void setOwner(Player* newOwner);
    bool owned;
    bool isUtility;
    bool isRailroad;
    int houseCount;
    int hotelCount;
    Player* getOwner();
};

enum class SpecialAction {
    AdvanceToGo,
    BankDividend,
    GoBack3Spaces,
    GoToJail,
    GeneralRepairs,
    PoorTax,
    TripToReadingRailroad,
    WalkOnBoardwalk,
    ElectedChairman,
    LoanMaturity,
    GetOutOfJailFree,
    AdvanceToIllinois,
    AdvanceToStCharles,
    AssessStreetRepairs,
    AdvanceToNearestUtility,
    AdvanceToNearestRailroad,
    ElectricCompany,
    WaterWorks,
    LuxuryTax,
    CommunityChest,
    Jail,
    FreeParking,
    Chance
};

class SpecialProperty : public Property {
private:
    Game* game;
public:
    SpecialProperty(const std::string& name, Game* game, SpecialAction action);
    void landOn(Player& player) override;
    void executeAction(Player& player, SpecialAction action);
    SpecialAction action;
};

class Street : public Property {
private:
    struct ColorGroup& colorGroup;
    int price;
    int rent;
    int housePrice;
    int hotelPrice;

public:
    Street(const std::string& name, int price, int rent, int housePrice, int hotelPrice, struct ColorGroup& colorGroup);
    void landOn(Player& player) override;
    void buildHouse(Player& player);
    int calculateRent() const;
};

class Train : public Property {
private:
    int cost;
    int taxPerTrain;

public:
    Train(const std::string& name, int cost, int taxPerTrain);
    void landOn(Player& player) override;
};
#endif // PROPERTY_H
