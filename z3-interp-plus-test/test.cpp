#include <iostream>
#include "../include/z3++.h"
#include "../include/z3.h"

int main(){
  z3::context ctx;
  z3::expr x = ctx.int_const("x");
  z3::expr y = ctx.int_const("y");
  z3::expr a = x < y;

  std::cout 
    << a.qf_to_simplify() 
    << std::endl;

  return 0;
}
