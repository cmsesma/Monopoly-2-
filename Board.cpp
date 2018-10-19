#include "Board.h"
#include <iostream>
#include "MonopolyUtility.h"
#include "Player.h"
#include "Jail.h" //i added
#include "GoToJail.h" //i added
#include "FreeParking.h" //i added
#include "PayToBank.h"  //i added
#include "Whiteboard.h" //i added
#include "Space.h"//i added

Monopoly::Board::Board(const std::string& boardFileName, GameState& gameState, Rules& rules) {

  CSVReader boardFile(boardFileName);
  constexpr int num_lines_to_skip = 4;

  if (boardFile.good()) {
    boardFile.skip_field();
    const int numSpaces = boardFile.get_next_field_as_int();

    std::shared_ptr<Whiteboard> white_board_pointer = std::make_shared<Whiteboard> ();

    for (int i = 0; i < num_lines_to_skip; ++i) {
      boardFile.skip_line();
    }

    for (int i = 0; i < numSpaces; ++i) {

      std::string space_type_string = boardFile.get_next_field();
      //std::cout << "printing in board.cpp ---" << space_type_string << std::endl;

      if (space_type_string == "Go"){
        //std::cout << "Made it in go if statement of board.cpp" << std::endl;
        spaces.push_back(std::make_unique<Go> (space_type_string, boardFile, i, gameState));
        //boardFile.skip_line(); // skip the remainder of the line in the file

      } else if (space_type_string == "Property"){
        //std::cout << "Made it in property if statement of board.cpp" << std::endl;
        spaces.push_back(std::make_unique<Property> (space_type_string, boardFile, rules, i, gameState));

      }else if (space_type_string == "Jail"){
        //std::cout << "Made it in jail if statement of board.cpp" << std::endl;
        spaces.push_back(std::make_unique<Jail> (space_type_string, boardFile, i, gameState));

      }else if (space_type_string == "FreeParking"){
        //std::cout << "Made it in freparking if statement of board.cpp" << std::endl;
        spaces.push_back(std::make_unique<FreeParking> (white_board_pointer, space_type_string, boardFile, i, gameState));

      } else if (space_type_string == "GoToJail"){
        //std::cout << "Made it in gotojail if statement of board.cpp" << std::endl;
        spaces.push_back(std::make_unique<GoToJail> (space_type_string, boardFile, i, gameState));

      }else if (space_type_string == "Pay"){
        //std::cout << "Made it in pay if statement of board.cpp" << std::endl;
        spaces.push_back(std::make_unique<PayToBank> (white_board_pointer, space_type_string, boardFile, rules, i, gameState));
      }
    }


    for (int i = 0; i < numSpaces; ++i) {
      if (spaces[i]->getSpaceType() == SpaceType::goToJail) {
        //spaces[i].
        GoToJail& tempVarGoToJail = static_cast<GoToJail& > (*spaces[i]);
        Jail& tempVarJailSpace = static_cast<Jail& > (*spaces[tempVarGoToJail.getindex_of_space_of_jail_space()]);
        tempVarGoToJail.setJail(tempVarJailSpace.getName(), tempVarJailSpace.getHow_long_in_jail_for(), tempVarJailSpace.getAmount_to_pay_to_get_out_of_jail());
        //setJail(jail);
      }
    }

    Monopoly::Space::length_of_longest_space_name = calc_length_of_longest_space_name();
    Monopoly::Space::length_of_longest_space_name =
        Utility::max(Monopoly::Space::length_of_longest_space_name, std::string("Space Name").size());

  } else {
    std::cout << "Failed to open board file: " << boardFileName << std::endl;
  }
}

void Monopoly::Board::display() const {

  //const std::string header("Space Number | Space Name | Owner | Upgrades | Players");

  //std::cout << header << std::endl;
  const std::string spaceNumber("Space Number");
  const std::string spaceName("Space Name");
  const std::string owner("Owner");
  const std::string Upgrades("Upgrades");
  const std::string playersString("Players");
  const auto frmt_flags = std::cout.flags();
  std::cout.setf(std::ios::left);

  std::cout << spaceNumber; std::cout << " | ";
  std::cout.width(Space::length_of_longest_space_name);
  std::cout << spaceName; std::cout << " | ";

  std::cout.width(Player::length_of_longest_player_name);
  std::cout << owner; std::cout << " | ";

  std::cout.width(Upgrades.size());
  std::cout << Upgrades << " | ";

  std::cout.width(Player::length_of_longest_player_name);
  std::cout << playersString; std::cout << std::endl;

  int i = 0;
  for (const auto& space : spaces) {
    std::cout.width(spaceNumber.size());
    std::cout << i << " | ";
    space->display();
    std::cout << std::endl;
    ++i;
  }
  std::cout.flags(frmt_flags);
}

unsigned long Monopoly::Board::calc_length_of_longest_space_name() const {
  std::vector<std::string> space_names;
  for (const auto& space : spaces) {
    space_names.emplace_back(space->getName());
  }
  return Utility::get_max_string_length(space_names);
}

Monopoly::Space& Monopoly::Board::getSpace(int spaceNum) {
  return *spaces[spaceNum];
}

Monopoly::Go& Monopoly::Board::getGoSpace() {
  for (auto& space : spaces) {
    if (space->getSpaceType() == SpaceType::goSpace) {
      return static_cast<Go& > (*space);
    }
  }
  //this line should never execute
  return static_cast<Go& >(*spaces[0]);
}

int Monopoly::Board::getNumSpaces() const {
  return static_cast<int>(spaces.size());
}

const std::vector<std::unique_ptr<Monopoly::Space>>& Monopoly::Board::getSpaces() const {
  return spaces;
}

void Monopoly::Board::removeAllPlayers() {
  for (auto& space : spaces) {
    space->removeAllPlayers();
  }
}



