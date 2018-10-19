
#ifndef HW4MONOPOLY_JAIL_H
#define HW4MONOPOLY_JAIL_H
#include "Space.h"
#include "Player.h"

namespace Monopoly {
class Jail: public Space {
  class Board;
 public:
  explicit Jail(std::string space_type_string, CSVReader& boardFile, const int spaceNumber, GameState& gameState);
  int getHow_long_in_jail_for() const;
  int getAmount_to_pay_to_get_out_of_jail() const;
  virtual const std::string& getName() const override;
  void display() const override ;

  virtual void activate(Player& activatingPlayer) override;

 private:
  int how_long_in_jail_for;
  int amount_to_pay_to_get_out_of_jail;
 private:
  std::string name;

};
}
#endif //HW4MONOPOLY_JAIL_H
