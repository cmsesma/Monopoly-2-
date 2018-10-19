#include "GoToJail.h"
#include <iostream>

//create variable for player for how long and if in jail
//jail call set/get for the player

Monopoly::GoToJail::GoToJail(std::string space_type_string, CSVReader& boardFile, const int spaceNumber, GameState& gameState) : Space(space_type_string, boardFile, spaceNumber, gameState) {
  //spaceType = SpaceType::goToJail;
  //salary = boardFile.get_next_field_as_int();
  name = boardFile.get_next_field();
  index_of_space_of_jail_space = boardFile.get_next_field_as_int();
  boardFile.skip_line();
  //std::cout << "printing in gotojail.cpp NAME: " << name << std::endl;
  //std::cout << "printing in gotojail.cpp how long in jail for: " << index_of_space_of_jail_space << std::endl;


}


void Monopoly::GoToJail::activate(Player& activatingPlayer){

  std::cout << activatingPlayer.getName() << ", you were sent to " << Jailname << " for " << how_long << " turns" << std::endl;

  int newLocation = index_of_space_of_jail_space;
  //int timesPastGo = 0; //dont pass go & dont collect salary


  //newLocation %= this->board.getNumSpaces();
  //newLocation %= gameState.getBoard().
  activatingPlayer.moveTo(gameState.getBoard().getSpace(newLocation));

  //send player to jail, use index

  activatingPlayer.setInJail(); //sets it so player is in jail
  activatingPlayer.setHowLongInJail(how_long);
  activatingPlayer.setPay_to_get_out(amount_to_pay_to_get_out);

  if (gameState.getRules().isPut_money_in_free_parking()){
    activatingPlayer.setput_money_in_free_parking_is_true(1);
  }

  //tell player for how long, need to access from jail space

}

void Monopoly::GoToJail::setJail(std::string Jailname, int how_long, int amount_to_pay_to_get_out){
  this->Jailname = Jailname;
  this->how_long = how_long;
  this->amount_to_pay_to_get_out = amount_to_pay_to_get_out;

}

void Monopoly::GoToJail::display() const{
  const auto frmt_flags = std::cout.flags();

  //display space name
  std::cout.width(length_of_longest_space_name);
  std::cout << getName() << " | ";

  //display owner
  std::cout.width(Monopoly::Player::length_of_longest_player_name);


  std::cout << "None" << " | "; //no one owns gotojail spaces
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
int Monopoly::GoToJail::getindex_of_space_of_jail_space() const {
  return index_of_space_of_jail_space;
}



const std::string& Monopoly::GoToJail::getName() const {
  return name;
}
