

#ifndef HW4MONOPOLY_PROPERTY_H
#define HW4MONOPOLY_PROPERTY_H

#include <string>
#include "CSVReader.h"
#include "Rules.h"
#include "Space.h" //I added

namespace Monopoly {
class Player;
class Space;

class Property: public Space { //needs to be derived from space
 public:
  explicit Property(std::string space_type_string, CSVReader& boardFile, const Rules& rules, const int spaceNumber, GameState& gameState);
  void setOwner(Player* owner);

  int getSetId() const;
  int getIntraSetId() const;

  virtual const std::string& getName() const override;

  int getCost() const;
  int getHouse_cost() const;
  int getHotel_cost() const;
  int getRent() const;
  int getRent_with_house() const;
  int getRent_with_hotel() const;
  Player* getOwner() const;
  std::string getOwnerName() const;
  int calculateRent(const Rules& rules) const;
  int getNumHousesOn() const;
  int getNumHotelsOn() const;
  int getNumUpgrades() const;
  int getValue() const;
  int getLanding_multiplier() const;
  void setLanding_multiplier(int landing_multiplier);
  bool isFullyUpgraded() const;
  bool nextUpgradeIsHouse() const;
  bool nextUpgradeIsHotel() const;
  void upgrade();
  void downgrade();
  std::string getUpgradesString() const;
  int getUpgradeCost() const;
  void setNumHousesOn(int numHousesOn);
  void setNumHotelsOn(int numHotelsOn);

  virtual void display() const override ;
  virtual void activate(Player& activatingPlayer) override ;


 private:
  int setId;
  int intraSetId;
  std::string name;
  int cost;
  int house_cost;
  int hotel_cost;
  int rent;
  int rent_with_house;
  int rent_with_hotel;
  Player* owner;
  int landing_multiplier;
  int numHousesOn;
  int numHotelsOn;
  const Rules& rules;

};
}



#endif //HW4MONOPOLY_PROPERTY_H
