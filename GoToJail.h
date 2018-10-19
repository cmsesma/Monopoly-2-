#ifndef HW4MONOPOLY_GOTOJAIL_H
#define HW4MONOPOLY_GOTOJAIL_H
#include "Space.h"
#include "Player.h"
#include "GameState.h" //i added
#include "Jail.h" //I added

namespace Monopoly {
class GoToJail: public Space {
  class Board;
 public:
  explicit GoToJail(std::string space_type_string, CSVReader& boardFile, const int spaceNumber, GameState& gameState);
  virtual const std::string& getName() const override;
  void display() const override ;

  int getindex_of_space_of_jail_space() const;

  void setJail(std::string Jailname, int how_long, int amount_to_pay_to_get_out);


  virtual void activate(Player& activatingPlayer) override;

 private:
  std::string name;
  int index_of_space_of_jail_space;
  //Jail jail;
  std::string Jailname;
  int how_long;
  int amount_to_pay_to_get_out;
};
}

#endif //HW4MONOPOLY_GOTOJAIL_H
