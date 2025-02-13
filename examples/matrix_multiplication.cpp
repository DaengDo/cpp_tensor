#include <iostream>

#include "../src/matrix/matrix.h"
#include "../src/tensor/tensor.h"

using namespace matrix;

int main() {
  std::cout << "58p\n";
  // 58p 3.8 - (1)
  multiplication(Tensor({1, 2, 3}), Tensor({{4}, {5}, {6}})).print();
  // 58p 3.8 - (2)
  multiplication(Tensor({{3}, {-1}, {0}}), Tensor({1, 2, 3, 4})).print();
  // 58p 3.8 - (3)
  multiplication(Tensor({{1, 1, 0}, {-3, 2, 1}}), Tensor({{2, -3}, {1, 2}, {0, -1}})).print();
  // 58p 3.8 - (4)
  multiplication(Tensor({{1, -2}, {3, 2}}), Tensor({{2, 0}, {-1, -2}})).print();

  std::cout << "72page\n";
  // 72p 7 - (1)
  multiplication(Tensor({0, 1, 2}), Tensor({{4, 2}, {1, 3}, {-2, 1}})).print();
  // 72p 7 - (2)
  multiplication(Tensor({{0, 1, 2}, {2, 3, 1}}), Tensor({{4, 2}, {1, 3}, {-2, 1}})).print();
  // 72p 7 - (3)
  multiplication(Tensor({{1, 0}, {2, 1}}), Tensor({{3, 2}, {-1, 1}})).print();
  // 72p 7 - (4)
  multiplication(Tensor({{2, -2}, {1, 4}}), Tensor({{1, -2}, {1, 3}})).print();

  std::cout << "73page\n";
  // 73p 8 - (1)
  multiplication(Tensor({1, 2}), Tensor({{2}, {-1}})).print();
  // 73p 8 - (2)
  multiplication(Tensor({{2, -6}, {-1, 3}}), Tensor({{3}, {1}})).print();
  // 73p 8 - (3)
  multiplication(Tensor({{1, 2, 3}, {3, -1, 2}, {4, -2, 2}}), Tensor({{5}, {5}, {-5}})).print();
  // 73p 8 - (4)
  multiplication(Tensor({{6, -9}, {-4, 6}}), Tensor({{6, 12}, {4, 8}})).print();

  return 0;
}
