#include "PayToBank.h"
#include <iostream>
#include "GameState.h"

Monopoly::PayToBank::PayToBank(std::shared_ptr<Whiteboard> white_board_pointer, std::string space_type_string, CSVReader& boardFile, Rules& rules, const int spaceNumber, GameState& gameState) : Space(space_type_string, boardFile, spaceNumber, gameState) {
  //spaceType = SpaceType::payToBank;
  this->white_board_pointer = white_board_pointer;
  name = boardFile.get_next_field();
  amount_money_for_free_parking = boardFile.get_next_field_as_int();
  //std::cout << "printing in paytobank.cpp" << name << std::endl;
  //std::cout << "printing in paytobank.cpp" << amount_money_for_free_parking << std::endl;
  boardFile.skip_line();

}

void Monopoly::PayToBank::payJailMoney(int money){
  white_board_pointer->adder(money);
}


void Monopoly::PayToBank::activate(Player& activatingPlayer){
  //if rules for put money in free parking is yes or no

 if (activatingPlayer.getCash() > amount_money_for_free_parking){  //they have enough money to pay
   if (gameState.getRules().isPut_money_in_free_parking()){ //pay to free parking
     std::cout << activatingPlayer.getName() << " paid the bank $" << amount_money_for_free_parking << " for landing on " << name << std::endl;

     white_board_pointer->adder(amount_money_for_free_parking); //put money in free parking pool


     activatingPlayer.setCash(activatingPlayer.getCash()-amount_money_for_free_parking);

   } else { //pay to bank
     std::cout << activatingPlayer.getName() << " paid the bank $" << amount_money_for_free_parking << " for landing on " << name << std::endl;
     activatingPlayer.payBank(amount_money_for_free_parking); //subtracts money from player
     //activatingPlayer.setCash(activatingPlayer.getCash()-amount_money_for_free_parking);
   }

 } else { //they dont have enough money to pay, sell properties
   unsigned long sell_num;
   int amount = amount_money_for_free_parking;

   std::vector<Property*> downgradeableProperties = activatingPlayer.getDowngradeableProperties(gameState.getRules());
   while(activatingPlayer.getCash() < amount && downgradeableProperties.size() > 0){
     std::cout << "You have $" << activatingPlayer.getCash() << " but you owe $" << amount << std::endl;
     std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;
     for (unsigned long i = 0; i < downgradeableProperties.size(); ++i) {
       std::cout << i << ". " << downgradeableProperties.at(i)->getName() << " [$"
                 << downgradeableProperties.at(i)->getUpgradeCost()  / 2<< "]" << std::endl;
     }
     std::cout << "Your choice: ";
     std::cin >> sell_num;
     downgradeableProperties.at(sell_num)->downgrade();
     downgradeableProperties = activatingPlayer.getDowngradeableProperties(gameState.getRules());
   }

   if (activatingPlayer.getCash() >= amount) {
     if (gameState.getRules().isPut_money_in_free_parking()){ //put the money in free parking money pool
       std::cout << activatingPlayer.getName() << " paid the bank $" << amount_money_for_free_parking << " for landing on " << name << std::endl;

       white_board_pointer->adder(amount_money_for_free_parking); //put money in free parking pool
       activatingPlayer.setCash(activatingPlayer.getCash()-amount_money_for_free_parking);

     } else {
       std::cout << activatingPlayer.getName() << " paid the bank $" << amount_money_for_free_parking << " for landing on " << name << std::endl;
       activatingPlayer.payBank(amount_money_for_free_parking);//subtracts money from player
       //activatingPlayer.setCash(activatingPlayer.getCash()-amount_money_for_free_parking);
     }

   } else {
     if (gameState.getRules().isPut_money_in_free_parking()){

       white_board_pointer->adder(amount_money_for_free_parking); //put money in free parking pool
       std::cout << activatingPlayer.getName() << " went bankrupt by landing on " << getName() << std::endl;;
       activatingPlayer.setCash(activatingPlayer.getCash()-amount_money_for_free_parking);
        //FIX
       gameState.removeFromGame(activatingPlayer);
       //propertyManager.givePropertiesTo(owner.propertyManager); // give all of our properties to the bank
       //owner.propertyManager.updateOwner(owner); // the bank we are paying to now owns all those properties

     } else {
       std::cout << activatingPlayer.getName()  << " went bankrupt by landing on " << getName() << std::endl;;
       activatingPlayer.payBank(amount_money_for_free_parking);//subtracts money from player
       //activatingPlayer.setCash(activatingPlayer.getCash()-amount_money_for_free_parking);
       //FIX
       gameState.removeFromGame(activatingPlayer);

       //propertyManager.givePropertiesTo(owner.propertyManager); // give all of our properties to the bank
       //owner.propertyManager.updateOwner(owner); // the bank we are paying to now owns all those properties
     }
   }

 }
}

void Monopoly::PayToBank::display() const{
  const auto frmt_flags = std::cout.flags();

  //display space name
  std::cout.width(length_of_longest_space_name);
  std::cout << getName() << " | ";

  //display owner
  std::cout.width(Monopoly::Player::length_of_longest_player_name);

  std::cout << "None" << " | ";
  std::cout << "         | ";


  std::cout.flags(frmt_flags);


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

int Monopoly::PayToBank::getAmount_money_for_free_parking() const {
  return amount_money_for_free_parking;
}

const std::string& Monopoly::PayToBank::getName() const {
  return name;
}
