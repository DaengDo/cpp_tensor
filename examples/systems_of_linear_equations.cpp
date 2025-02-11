#include "../src/matrix/matrix.h"
#include "../src/tensor/tensor.h"

void solve_using_gauss_jordan(const Tensor matrix) {
  matrix.print();
  for (auto sol : matrix::solve(matrix)) {
    std::cout << sol << " ";
  }
  std::cout << "\n";
}

int main() {
  // 40p 03
  solve_using_gauss_jordan({{2, 3, -1, 4}, {4, -2, 6, 8}, {1, 0, 2, 10}});

  // 41p 05-01
  solve_using_gauss_jordan({{2, -1, 2, 3}, {1, 2, -1, 2}, {3, 2, 1, 6}});

  // 41p 05-02
  solve_using_gauss_jordan({{1, 1, -2, 5}, {1, -1, 1, 0}, {3, 2, 4, 7}});

  // 41p 05-03
  solve_using_gauss_jordan({{1, 2, 3, 0, 2, -3}, {0, 2, 0, 2, -4, 6}, {0, 0, 1, 0, -1, 2}});

  // 41p 05-04
  solve_using_gauss_jordan({{0, 3, 6, 12}, {3, 7, 5, 19}, {2, -1, 4, 9}});

  // 41p 07
  solve_using_gauss_jordan({{1, 1, -3, 5}, {0, 2, 6, 2}, {0, 0, 3, -6}});

  return 0;
}