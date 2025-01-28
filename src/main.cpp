#include <iostream>

#include "tensor.h"

int main() {
  std::cout << "-----------scalar----------\n";
  Tensor a = Tensor(5);  // scalar
  a.print();

  std::cout << "-----------vector----------\n";

  Tensor b = Tensor({0, 1, 2});  // 1x3
  b.print();

  std::cout << "-----------matrix----------\n";

  Tensor c = Tensor({{0, 1}, {1, 0}});  // 2x2
  c.print();

  std::cout << "-----------tensor----------\n";

  Tensor d =
      Tensor({{{0, 1, 2}, {3, 4, 5}}, {{6, 7, 8}, {9, 10, 11}}});  // 2x2x3
  d.print();

  return 0;
}
