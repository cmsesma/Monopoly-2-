
#ifndef HW4MONOPOLY_GO_H
#define HW4MONOPOLY_GO_H

#include <string>
#include "CSVReader.h"
#include "Space.h" //I added
#include "Player.h"
//#include "GameState.h"

namespace Monopoly {
class Go: public Space {
  class Board;
 public:
  explicit Go(std::string space_type_string, CSVReader& boardFile, const int spaceNumber, GameState& gameState);
  int getSalary() const;
  virtual const std::string& getName() const override;
  void display() const override ;

  virtual void activate(Player& activatingPlayer) override;

 private:
  int salary;
  int landing_multiplier;
 public:
  int getLanding_multiplier() const;
  void setLanding_multiplier(int landing_multiplier);
 private:
  std::string name;

};
}


#endif //HW4MONOPOLY_GO_H
