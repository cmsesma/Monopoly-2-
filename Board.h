
#ifndef HW4MONOPOLY_BOARD_H
#define HW4MONOPOLY_BOARD_H

#include <vector>
#include <string>
#include "Space.h"
#include "Rules.h"
#include "Go.h"
#include "Whiteboard.h"

namespace Monopoly {
//class Space;
class GameState;
class Board {
 public:
  Board(const std::string& boardFileName, GameState& gameState, Rules& rules);
  void display() const;
  Space& getSpace(int spaceNum);
  Go& getGoSpace();
  int getNumSpaces() const;
  const std::vector<std::unique_ptr<Space> >& getSpaces() const;
  void removeAllPlayers();


 private:
  //std::vector<Space> spaces;
  std::vector<std::unique_ptr<Space> > spaces;

  unsigned long calc_length_of_longest_space_name() const;

};
}
//std::vector<std::unique_ptr<Space>> AllSpaces;

#endif //HW4MONOPOLY_BOARD_H
