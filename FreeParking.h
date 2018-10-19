#ifndef HW4MONOPOLY_FREEPARKING_H
#define HW4MONOPOLY_FREEPARKING_H
#include "Space.h"
#include "Player.h"
#include "Whiteboard.h" //i added


namespace Monopoly {
class FreeParking: public Space {
  class Board;
 public:
  explicit FreeParking(std::shared_ptr<Whiteboard> white_board_pointer, std::string space_type_string, CSVReader& boardFile, const int spaceNumber, GameState& gameState);
  virtual const std::string& getName() const override;
  void display() const override ;

  virtual void activate(Player& activatingPlayer) override;


 private:
  std::string name;
  std::shared_ptr<Whiteboard> white_board_pointer;

};
}


#endif //HW4MONOPOLY_FREEPARKING_H
