#ifndef HW4MONOPOLY_PAYTOBANK_H
#define HW4MONOPOLY_PAYTOBANK_H
#include "Space.h"
#include "Player.h"
#include "Whiteboard.h" //i added

namespace Monopoly {
class PayToBank: public Space {
  class Board;
 public:
  explicit PayToBank(std::shared_ptr<Whiteboard> white_board_pointer, std::string space_type_string, CSVReader& boardFile, Rules& rules, const int spaceNumber, GameState& gameState);
  int getAmount_money_for_free_parking() const;
  virtual const std::string& getName() const override;
  void display() const override ;

  virtual void activate(Player& activatingPlayer) override;

  void payJailMoney(int money);

 private:
  int amount_money_for_free_parking;
 private:
  std::string name;
  std::shared_ptr<Whiteboard> white_board_pointer;

};
}
#endif //HW4MONOPOLY_PAYTOBANK_H
