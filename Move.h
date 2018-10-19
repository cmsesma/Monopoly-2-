

#ifndef HW4MONOPOLY_MOVE_H
#define HW4MONOPOLY_MOVE_H

#include "DiceRoller.h"
#include "Rules.h"

namespace Monopoly {
enum class MoveAction { rollDice = 1, buyUpgrade = 2, sellUpgrade = 3, leaveGame = 4 , ERROR };
class Move {
 public:
  static int MoveActionToInt(MoveAction action);
  Move();
  MoveAction getAction() const;
  Move(const int moveNumber);
  bool endsTurn(const DiceRoller& diceRoller, const Rules& rules);
 private:
  MoveAction action;
};
}


#endif //HW4MONOPOLY_MOVE_H
