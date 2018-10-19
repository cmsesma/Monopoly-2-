#include "Jail.h"
#include <iostream>

Monopoly::Jail::Jail(std::string space_type_string, CSVReader& boardFile, const int spaceNumber, GameState& gameState) : Space(space_type_string, boardFile, spaceNumber, gameState) {
  //spaceType = SpaceType::jail;
  //salary = boardFile.get_next_field_as_int();
  name = boardFile.get_next_field();
  how_long_in_jail_for = boardFile.get_next_field_as_int();
  amount_to_pay_to_get_out_of_jail = boardFile.get_next_field_as_int();

  boardFile.skip_line();
  //std::cout << "printing in jail.cpp NAME: " << name << std::endl;
  //std::cout << "printing in go.cpp how long in jail for: " << how_long_in_jail_for << std::endl;
  //std::cout << "printing in go.cpp amount to pay to get out of jail: " << amount_to_pay_to_get_out_of_jail << std::endl;

}


void Monopoly::Jail::activate(Player& activatingPlayer){
  if (activatingPlayer.getin_jail_or_not() == 1){ //if in jail
    //in jail upgrade/downgrade properties
    //pay get out of jail fee beginning of turn
    //roll double out of jail
    //if been in jail for max turns pay or go bankrupt
    //if free parking enabled money goes to freee parking pool
    std::cout << activatingPlayer.getName() << "you are in jail for " << how_long_in_jail_for << " turns" << std::endl;
    //std::cout << "Working on this part";


  } else{ //if land on space=visiting so do nothing

  }


}

void Monopoly::Jail::display() const{
  const auto frmt_flags = std::cout.flags();

  //display space name
  std::cout.width(length_of_longest_space_name);
  std::cout << getName() << " | ";

  //display owner
  std::cout.width(Monopoly::Player::length_of_longest_player_name);


  std::cout << "None" << " | "; //no one owns jail spaces
  std::cout << "         | ";

  std::cout.flags(frmt_flags);

  auto player = playersOnSpace.cbegin();
  for (; player != playersOnSpace.cend(); ++player) {
    if (player + 1 == playersOnSpace.cend()) {
      break;
    }

    (*player)->display();
    std::cout << ", ";

  }

  if (player != playersOnSpace.cend()) {
    (*player)->display();
  }

}
int Monopoly::Jail::getAmount_to_pay_to_get_out_of_jail() const {
  return amount_to_pay_to_get_out_of_jail;
}

int Monopoly::Jail::getHow_long_in_jail_for() const {
  return how_long_in_jail_for;
}

const std::string& Monopoly::Jail::getName() const {
  return name;
}
