#include "FreeParking.h"
#include <iostream>
#include "PayToBank.h"
Monopoly::FreeParking::FreeParking(std::shared_ptr<Whiteboard> white_board_pointer, std::string space_type_string, CSVReader& boardFile, const int spaceNumber, GameState& gameState) : Space(space_type_string, boardFile, spaceNumber, gameState) {
  this->white_board_pointer = white_board_pointer;

  name = boardFile.get_next_field();
  //std::cout << "printing in freeparking.cpp NAME: " << name << std::endl;

  boardFile.skip_line();


}


void Monopoly::FreeParking::activate(Player& activatingPlayer){
  if (white_board_pointer->getamount_total_pay() > 0){ //there is money
    std::cout << activatingPlayer.getName() << "got $" << white_board_pointer->getamount_total_pay() << "for landing on " << name << std::endl;
    activatingPlayer.setCash(activatingPlayer.getCash()+white_board_pointer->getamount_total_pay());
    white_board_pointer->resetZero();
  } else { //if theres no money do nothing
  }
}

void Monopoly::FreeParking::display() const{
  const auto frmt_flags = std::cout.flags();

  //display space name
  std::cout.width(length_of_longest_space_name);
  std::cout << getName() << " | ";

  //display owner
  std::cout.width(Monopoly::Player::length_of_longest_player_name);


  std::cout << "None" << " | "; //no one owns free parking spaces
  std::cout << "         | ";

  //what to print out for free parking

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



const std::string& Monopoly::FreeParking::getName() const {
  return name;
}
