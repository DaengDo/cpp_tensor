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

  Tensor d = Tensor({{{0, 1, 2}, {3, 4, 5}}, {{6, 7, 8}, {9, 10, 11}}});  // 2x2x3
  d.print();

  std::cout << "-----------scalar addition----------\n";

  Tensor one = Tensor(1);
  Tensor two = Tensor(2);
  Tensor three = one + two;
  three.print();

  std::cout << "-----------vector addition----------\n";

  Tensor vec1 = Tensor({1, 2, 3});
  Tensor vec2 = Tensor({4, 5, 6});
  Tensor vec3 = vec1 + vec2;
  vec3.print();

  std::cout << "-----------matrix addition----------\n";

  Tensor mat1 = Tensor({{1, 2}, {3, 4}});
  Tensor mat2 = Tensor({{5, 6}, {7, 8}});
  Tensor mat3 = mat1 + mat2;
  mat3.print();

  std::cout << "-----------tensor addition----------\n";

  Tensor ten1 = Tensor({{{0, 1, 2}, {3, 4, 5}}, {{6, 7, 8}, {9, 10, 11}}});
  Tensor ten2 = Tensor({{{0, 1, 2}, {3, 4, 5}}, {{6, 7, 8}, {9, 10, 11}}});
  Tensor ten3 = ten1 + ten2;
  ten3.print();

  return 0;
}
