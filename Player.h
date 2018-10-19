
#ifndef HW4MONOPOLY_PLAYER_H
#define HW4MONOPOLY_PLAYER_H

#include <string>
#include <map>

#include "Property.h"
#include "Space.h"
#include "PropertyManager.h"
#include "Rules.h"
#include "Move.h"


namespace Monopoly {
class Player {
 public:
  static unsigned long length_of_longest_player_name;
  Player(int id, const std::string& name, int cash, Space* spaceOn, const PropertyManager& propertyManager);
  Player(const Player& player) = default;
  Space& getSpaceOn();
  virtual ~Player();

  void setOn(Space& space, bool activateSpace = true);
  void moveTo(Space& space, bool activateSpace = true);

  const std::string& getName() const;
  int getCash() const;
  void setCash(int cash);
  void giveCash(const int amount);

  void purchase(Property& property, const int amount);

  bool getBuyDecision(const Property& property) const;

  void payPlayer(Monopoly::Player& owner, const Property& propertyOn, const Rules& rules);
  bool ownsAllPropertiesInSet(const int setId) const;
  int getNetWorth() const;
  void refreshReferencesTo();
  Move getMove();

  std::vector<Property*> getUpgradeableProperties(const Rules& rules) const;
  std::vector<Property*> getDowngradeableProperties(const Rules& rules) const;
  void payBank(const int amount);

  void display();
  int getId() const;


  int in_jail_or_not = 0; //0 means not in jail
  int how_long_in_jail_for = 0;
  int pay_to_get_out = 0;
  int put_money_in_free_parking_is_true = 0; //1 means true

  int getHowlongInJailfor();
  int getin_jail_or_not();
  int getpay_to_get_out();
  int getput_money_in_free_parking_is_true();

  void setput_money_in_free_parking_is_true(int put_money_in_free_parking_is_true);
  void setPay_to_get_out(int pay_to_get_out);
  void setHowLongInJail(int how_long_in_jail_for);
  void setInJail();
  void setOutofJail();

  void decreaseHowLongInJail();

 private:
  int id;
  std::string name;
  int cash;
  Move current_move;

  //PayToBank& payToBank;

  Space* spaceOn;
  PropertyManager propertyManager;


  //std::shared_ptr<Whiteboard> white_board_pointer; //i added

};
}


#endif //HW4MONOPOLY_PLAYER_H
