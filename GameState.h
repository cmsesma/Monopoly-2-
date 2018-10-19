
#ifndef HW4MONOPOLY_GAMESTATE_H
#define HW4MONOPOLY_GAMESTATE_H

#include <vector>
#include <string>
#include <fstream>
#include <memory>

#include "Rules.h"
#include "Move.h"
#include "Board.h"
#include "DiceRoller.h"
#include "Player.h"


namespace Monopoly {
class GameState {
  //class Board;
  friend Space;
 public:
  static std::vector<std::string> get_player_names();
  GameState(const std::string& RulesFileName,
            const std::string& BoardFileName,
            const std::string& RandomFileName,
            const std::vector<std::string>& playerNames);

  void playGame();
  bool isGameOver() const;
  Player& getCurrentPlayer();
  void make_move(Player& player, Move& move);
  void declareWinner();
  void changeTurn();
  void removeFromGame(Player& player);
  void auction(Property& property);

  Board& getBoard();//i added

  const Rules getRules();

  void display() const;

 private:
  void buyUpgrade();
  void sellUpgrade();
  void rollDice(Monopoly::Player& player);


  Rules rules;
  Board board;
  DiceRoller diceRoller;
  int turn_count;
  unsigned long player_turn;
  std::vector<std::unique_ptr<Player> > players;
};
}



#endif //HW4MONOPOLY_GAMESTATE_H
