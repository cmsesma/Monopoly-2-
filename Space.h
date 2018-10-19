

#ifndef HW4MONOPOLY_SPACE_H
#define HW4MONOPOLY_SPACE_H

#include <memory>
#include <vector>

#include "CSVReader.h"
#include "Rules.h"

//#include "Go.h"
//#include "Property.h"

namespace Monopoly {
class Player;
class GameState;
enum class SpaceType { goSpace, propertySpace, freeParking, goToJail, jail, payToBank };

class Space { //space is base class
 public:
  static unsigned long length_of_longest_space_name;
  Space(std::string space_type_string, CSVReader& boardFile, int spaceNumber, GameState& gameState);
  int getSpaceNumber() const;
  std::string getspace_type_string() const;

  virtual void display() const = 0; //display this space to the screen
  virtual const std::string& getName() const = 0;
  void addPlayer(Player& player);
  void removePlayer(const Player& player);
  void removeAllPlayers();
  SpaceType getSpaceType() const;
  virtual void activate(Player& activatingPlayer) = 0; //handles what happens when a player lands on this space


  //int getSalary() const;
  //int getCost() const;
  //int getSetId() const;
  //int getIntraSetId() const;
  //int getBasicRent() const;

 protected:
  SpaceType spaceType;
  //std::unique_ptr<Go> goPtr;
  //std::unique_ptr<Property> propertyPtr;
  std::vector<Player*> playersOnSpace;
  int spaceNumber;
  std::string space_type_string;
  GameState& gameState;
};
}


#endif //HW4MONOPOLY_SPACE_H
