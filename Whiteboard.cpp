
#include "Whiteboard.h"

Monopoly::Whiteboard::Whiteboard() {

}

int Monopoly::Whiteboard::getamount_total_pay() {
  return amount_total_pay;
}

void Monopoly::Whiteboard::adder(int pay_value){
  amount_total_pay+= pay_value;
}

void Monopoly::Whiteboard::resetZero(){
  amount_total_pay= 0;
}