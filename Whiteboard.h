
#ifndef HW4MONOPOLY_WHITEBOARD_H
#define HW4MONOPOLY_WHITEBOARD_H


namespace Monopoly {
class Whiteboard {

 public:
  explicit Whiteboard();
  int getamount_total_pay();
  void adder(int pay_value);
  void resetZero();

 private:
  int amount_total_pay = 0;



};
}



#endif //HW4MONOPOLY_WHITEBOARD_H
