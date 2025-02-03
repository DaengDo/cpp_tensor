#include <iostream>

#include "matrix.h"
#include "tensor.h"

int main() {
  std::cout << "-----------scalar----------\n";
  Tensor a = Tensor(5);  // scalar
  a.print();
  (a + Tensor(1)).print();
  (a - Tensor(1)).print();

  std::cout << "-----------vector----------\n";

  Tensor b = Tensor({0, 1, 2});  // 1x3
  b.print();
  (b + Tensor({4, 5, 6})).print();
  (b - Tensor({4, 5, 6})).print();

  std::cout << "-----------matrix----------\n";

  Tensor c = Tensor({{0, 1}, {1, 0}});  // 2x2
  c.print();
  (c + Tensor({{1, 2}, {3, 4}})).print();
  (c - Tensor({{1, 2}, {3, 4}})).print();

  std::cout << "@@@@@@@@@@@@@@@@\n";

  matrix::swap_rows(c, 0, 1).print();

  matrix::swap_rows(Tensor({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}), 1, 2).print();

  matrix::scale_row(c, 0, 3).print();
  matrix::add_muliple_row(c, 0, 1, -3).print();

  std::cout << "find zero rows\n";
  for (auto zero_row_idx : matrix::find_zero_rows(c)) {
    std::cout << zero_row_idx << std::endl;
  }

  for (auto zero_row_idx : matrix::find_zero_rows(Tensor({{0, 0}, {1, 2}, {0, 0}, {3, 4}}))) {
    std::cout << zero_row_idx << std::endl;
  }

  std::cout << "@@@@@@@@@@@@@@@@\n";

  std::cout << "-----------tensor----------\n";

  Tensor d = Tensor({{{0, 1, 2}, {3, 4, 5}}, {{6, 7, 8}, {9, 10, 11}}});  // 2x2x3
  d.print();
  (d + Tensor({{{12, 13, 14}, {15, 16, 17}}, {{18, 19, 20}, {21, 22, 23}}})).print();
  (d - Tensor({{{12, 13, 14}, {15, 16, 17}}, {{18, 19, 20}, {21, 22, 23}}})).print();

  std::cout << "###########is_reduced_row_echoelon_form###########\n";

  std::cout << matrix::is_reduced_row_echoelon_form(Tensor({{0, 1, 0}, {0, 0, 1}})) << "\n";

  std::cout << "###########is_reduced_row_echoelon_form###########\n";

  return 0;
}
