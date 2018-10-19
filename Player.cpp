#include "Player.h"
#include <iostream>
#include <cctype>


unsigned long Monopoly::Player::length_of_longest_player_name;

Monopoly::Player::Player(int id,
                         const std::string& name,
                         int cash,
                         Space* spaceOn,
                         const PropertyManager& propertyManager)
    : id(id), name(name), cash(cash), spaceOn(spaceOn), propertyManager(propertyManager) {

  //this->white_board_pointer = white_board_pointer;

}

const std::string& Monopoly::Player::getName() const {
  return name;
}

int Monopoly::Player::getCash() const {
  return cash;
}

void Monopoly::Player::setCash(int cash) {
  Player::cash = cash;
}

void Monopoly::Player::giveCash(const int amount) {
  cash += amount;
}

Monopoly::Move Monopoly::Player::getMove() {
  if (getin_jail_or_not() == 1){

    if (how_long_in_jail_for != 0) {
      char choiceToPay;
      std::cout << name << " you are in jail for " << how_long_in_jail_for << " turns." << std::endl;
      decreaseHowLongInJail();

      if (getCash() > pay_to_get_out) {
        std::cout << "Would you like to pay $" << pay_to_get_out << " to leave jail early?" << std::endl;
        std::cout << "y for yes and n for no: ";
        std::cin >> choiceToPay;
        if (choiceToPay == 'y') { //move player out of jail & skip turn maybe?
          /*if (put_money_in_free_parking_is_true == 1){
            white_board_pointer->adder(pay_to_get_out);
          }*/
          in_jail_or_not = 0; //no longer in jail
          setCash(getCash() - pay_to_get_out);
        } //else continue

      }
    } else { //have been in jail for num of turns
      if (pay_to_get_out > getCash()){


        //first tries to downgrade to get money

        std::cout << name << " went bankrupt when paying to leave jail" << std::endl;
        setCash(getCash() - pay_to_get_out);
        /*if (put_money_in_free_parking_is_true == 1){
          white_board_pointer->adder(pay_to_get_out);
        }*/
        in_jail_or_not = 0;
        current_move = Move(4);
        return current_move;
      }
      if (put_money_in_free_parking_is_true == 1){
        //white_board_pointer->adder(pay_to_get_out);
        //std::cout << "PRINTING IN PLAYER.CPP" << white_board_pointer->getamount_total_pay() << std::endl;
        //payToBank.payJailMoney(pay_to_get_out);
      }
      std::cout << name << ", you had to pay $" << pay_to_get_out << " to get out of jail" << std::endl;
      in_jail_or_not = 0; //no longer in jail
      setCash(getCash() - pay_to_get_out);
    }
  }

  int move_number;
  std::cout << name << " please enter your move" << std::endl;
  std::cout << Move::MoveActionToInt(MoveAction::rollDice) <<" to roll dice" << std::endl;
  std::cout << Move::MoveActionToInt(MoveAction::buyUpgrade)
            << " to upgrade a property with a house or hotel" << std::endl;
  std::cout << Move::MoveActionToInt(MoveAction::sellUpgrade)
            << " to sell a house or hotel" << std::endl;
  std::cout << Move::MoveActionToInt(MoveAction::leaveGame) << " to leave the game" << std::endl;
  std::cout << "Your move: ";
  std::cin >> move_number;
  current_move = Move(move_number);

  return current_move;
}

void Monopoly::Player::display() {
  std::cout << '[' << name << " : $" << cash << ']';
}

int Monopoly::Player::getId() const {
  return id;
}

Monopoly::Space& Monopoly::Player::getSpaceOn() {
  return *spaceOn;
}

void Monopoly::Player::setOn(Space& space, bool activateSpace) {
  this->spaceOn = &space;
  space.addPlayer(*this);

  if (activateSpace) {
    space.activate(*this);
  }

}

void Monopoly::Player::moveTo(Monopoly::Space& space, bool activateSpace) {
  spaceOn->removePlayer(*this);
  setOn(space);

}

bool Monopoly::Player::getBuyDecision(const Monopoly::Property& property) const {
  char choice;
  std::cout << "Would you like to buy " << property.getName() << " for $" << property.getCost() << '?' << std::endl;
  std::cout << "Rent on " <<property.getName() << " is $" << property.getRent() << std::endl;
  std::cout << "Enter y for yes or n for no: ";
  std::cin >> choice;
  choice = static_cast<char>(tolower(choice));
  if (!(choice == 'y' || choice == 'n')) {
    std::cout << "Unknown choice of " << choice << " received for buy decision" << std::endl;
    return false;
  }
  return choice == 'y';
}

void Monopoly::Player::purchase(Property& property, const int amount) {
  cash -= amount;
  property.setOwner(this);
  propertyManager.takeOwnershipOf(property);
}

void Monopoly::Player::(Monopoly::Player& owner, const Property& propertyOn, const Rules& rules) {
  unsigned long sell_num;
  int amount = propertyOn.calculateRent(rules);

  std::vector<Property*> downgradeableProperties = getDowngradeableProperties(rules);
  while(cash< amount && downgradeableProperties.size() > 0){
    std::cout << "You have $" << cash << " but you owe $" << amount << std::endl;
    std::cout << "Pick an upgrade to sell to make up the difference" << std::endl;
    for (unsigned long i = 0; i < downgradeableProperties.size(); ++i) {
      std::cout << i << ". " << downgradeableProperties.at(i)->getName() << " [$"
                << downgradeableProperties.at(i)->getUpgradeCost()  / 2<< "]" << std::endl;
    }
    std::cout << "Your choice: ";
    std::cin >> sell_num;
    downgradeableProperties.at(sell_num)->downgrade();
    downgradeableProperties = getDowngradeableProperties(rules);
  }

  if (cash >= amount) {
    cash -= amount;
    owner.cash += amount;

    std::cout << name << " paid " << owner.name << " $" << amount << " for landing on " << propertyOn.getName()
              << std::endl;
  } else {
    owner.cash += cash;
    cash -= amount;
    propertyManager.givePropertiesTo(owner.propertyManager); // give all of our properties to the player we owe
    owner.propertyManager.updateOwner(owner); // the player we are paying to now owns all those properties
    std::cout << name << " went bankrupt to " << owner.name << " for landing on " << propertyOn.getName() << std::endl;;
  }
}

void Monopoly::Player::payBank(const int amount) {
  cash -=amount;
}

bool Monopoly::Player::ownsAllPropertiesInSet(const int setId) const {
  return propertyManager.ownsEntireSet(setId);
}

/**
 * Update all the references to this player so that they actually point to this player
 */
void Monopoly::Player::refreshReferencesTo() {
  propertyManager.updateOwner(*this);
  spaceOn->addPlayer(*this);
}

Monopoly::Player::~Player() {
  //spaceOn->removePlayer(*this);
}

int Monopoly::Player::getin_jail_or_not() { //getter
  return in_jail_or_not;
}
int Monopoly::Player::getput_money_in_free_parking_is_true() { //getter
  return put_money_in_free_parking_is_true;
}

int Monopoly::Player::getpay_to_get_out() { //getter
  return pay_to_get_out;
}

void Monopoly::Player::setInJail() { //set to in jail
  in_jail_or_not = 1;
}

void Monopoly::Player::setOutofJail() { //set to out of jail
  in_jail_or_not = 0;
}

int Monopoly::Player::getHowlongInJailfor() {
  return how_long_in_jail_for;
}
void Monopoly::Player::setput_money_in_free_parking_is_true(int put_money_in_free_parking_is_true) { //set to in jail
  this->put_money_in_free_parking_is_true = put_money_in_free_parking_is_true;
}


void Monopoly::Player::setHowLongInJail(int how_long_in_jail_for) { //set to in jail
  this->how_long_in_jail_for = how_long_in_jail_for;
}

void Monopoly::Player::decreaseHowLongInJail() { //set to in jail
  how_long_in_jail_for = how_long_in_jail_for - 1;
}

void Monopoly::Player::setPay_to_get_out(int pay_to_get_out) { //set to in jail
  this->pay_to_get_out = pay_to_get_out;
}


int Monopoly::Player::getNetWorth() const {

  return cash + propertyManager.getValue();
}

std::vector<Monopoly::Property*> Monopoly::Player::getUpgradeableProperties(const Rules& rules) const {
  return propertyManager.getUpgradeableProperties(rules, cash);
}

std::vector<Monopoly::Property*> Monopoly::Player::getDowngradeableProperties(const Monopoly::Rules& rules) const {
  return propertyManager.getDowngradeableProperties(rules);
}








