#include "Go.h"
#include <iostream>
#include "GameState.h"

Monopoly::Go::Go(std::string space_type_string, CSVReader& boardFile, const int spaceNumber, GameState& gameState) : Space(space_type_string, boardFile, spaceNumber, gameState), landing_multiplier(1) {
  //spaceType = SpaceType::goSpace;
  salary = boardFile.get_next_field_as_int();
  name = boardFile.get_next_field();

  //std::cout << "printing in go.cpp SALARY: " << salary << std::endl;

  //std::cout << "printing in go.cpp NAME: " << name << std::endl;
  boardFile.skip_line();



}

void Monopoly::Go::activate(Player& activatingPlayer){
  activatingPlayer.giveCash(getSalary() * (gameState.getRules().getSalary_multiplier_for_landing_on_go() - 1));

}

void Monopoly::Go::display() const{
  const auto frmt_flags = std::cout.flags();

  //display space name
  std::cout.width(length_of_longest_space_name);
  std::cout << getName() << " | ";

  //display owner
  std::cout.width(Monopoly::Player::length_of_longest_player_name);
    const std::string temp = "None";
    std::cout << temp << " | ";
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

int Monopoly::Go::getSalary() const {
  return salary;
}

const std::string& Monopoly::Go::getName() const {
  //std::cout << "here is the name for go" << name;

  return name;
}

int Monopoly::Go::getLanding_multiplier() const {
  return landing_multiplier;
}

void Monopoly::Go::setLanding_multiplier(int landing_multiplier) {
  this->landing_multiplier = landing_multiplier;
}


