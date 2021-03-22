#include <iostream>
#include "../include/z3++.h"
#include "../include/z3.h"

void test_only_non_neg_monomials(){
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
  z3::expr a6 = (x -x + 1 < y -y);
  z3::expr a7 = (x -x  < y -y + 12);

  a1 = a1.qf_to_simplify();
  a1_2 = a1_2.qf_to_simplify();
  a2 = a2.qf_to_simplify();
  a2_2 = a2_2.qf_to_simplify();
  a3 = a3.qf_to_simplify();
  a4 = a4.qf_to_simplify();
  a5 = a5.qf_to_simplify();
  a6 = a6.qf_to_simplify();
  a7 = a7.qf_to_simplify();

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
  std::cout << "a6" << std::endl;
  std::cout 
    << a6
    << std::endl;
  std::cout << "a7" << std::endl;
  std::cout 
    << a7
    << std::endl;
}

void qf_to_test(){
  z3::context ctx;
  z3::expr x = ctx.int_const("x");
  z3::expr y = ctx.int_const("y");
  z3::expr z = ctx.int_const("z");
  z3::expr a1 = (x <= y);
  z3::expr a2 = (x <= y - 12);
  z3::expr a3 = (x < y - 12);
  z3::expr a4 = (x + z < y - 12);
  z3::expr a5 = (x -x < y -y - 12);
  z3::expr a6 = (x -x < y -y + 12);

  a1 = a1.qf_to_simplify();
  a2 = a2.qf_to_simplify();
  a3 = a3.qf_to_simplify();
  a4 = a4.qf_to_simplify();
  a5 = a5.qf_to_simplify();
  a6 = a6.qf_to_simplify();

  std::cout << "Priting a1" << std::endl;
  std::cout << a1 << std::endl;
  std::cout << "Priting a2" << std::endl;
  std::cout << a2 << std::endl;
  std::cout << "Priting a3" << std::endl;
  std::cout << a3 << std::endl;
  std::cout << "Priting a4" << std::endl;
  std::cout << a4 << std::endl;
  std::cout << "Priting a5" << std::endl;
  std::cout << a5 << std::endl;
  std::cout << "Priting a6" << std::endl;
  std::cout << a6 << std::endl;
}

int main(){
  qf_to_test();
}
