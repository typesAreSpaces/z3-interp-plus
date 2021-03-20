#include <iostream>
#include "../include/z3++.h"
#include "../include/z3.h"

int main(){
  z3::context ctx;
  z3::expr x = ctx.int_const("x");
  z3::expr y = ctx.int_const("y");
  z3::expr a1 = (x < y + 12);
  z3::expr a1_2 = (x - y < 12);
  z3::expr a2 = (x < y - 12);
  z3::expr a2_2 = (x - y < - 12);
  z3::expr a3 = (x + 12 < y);
  z3::expr a4 = (x - 12 < y);
  z3::expr a5 = (x < y);

  std::cout << "simplifying a1" << std::endl;
  a1 = a1.simplify();
  std::cout << "qf_to_simplifying a1" << std::endl;
  a1 = a1.qf_to_simplify();
  std::cout << "qf_to_simplifying a1_2" << std::endl;
  a1_2 = a1_2.qf_to_simplify();
  std::cout << "qf_to_simplifying a2" << std::endl;
  a2 = a2.qf_to_simplify();
  std::cout << "qf_to_simplifying a2_2" << std::endl;
  a2_2 = a2_2.qf_to_simplify();
  std::cout << "qf_to_simplifying a3" << std::endl;
  a3 = a3.qf_to_simplify();
  std::cout << "qf_to_simplifying a4" << std::endl;
  a4 = a4.qf_to_simplify();
  std::cout << "qf_to_simplifying a5" << std::endl;
  a5 = a5.qf_to_simplify();

  std::cout << "a1" << std::endl;
  std::cout 
    << a1
    << std::endl;
  std::cout << "a1_2" << std::endl;
  std::cout 
    << a1_2 
    << std::endl;
  std::cout << "a2" << std::endl;
  std::cout 
    << a2 
    << std::endl;
  std::cout << "a2_2" << std::endl;
  std::cout 
    << a2_2
    << std::endl;
  std::cout << "a3" << std::endl;
  std::cout 
    << a3 
    << std::endl;
  std::cout << "a4" << std::endl;
  std::cout 
    << a4
    << std::endl;
  std::cout << "a5" << std::endl;
  std::cout 
    << a5
    << std::endl;

  return 0;
}
