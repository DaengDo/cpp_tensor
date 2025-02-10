선형대수학의 기본 원리를 직접 구현해보며 복습하기 위한 목적의 저장소 입니다.

- 텐서 자료구조

  ```cpp
  // scalar 3
  Tensor(3);
  // vector 1, 2, 3
  Tensor({1, 2, 3});
  // matrix 2x2 unit
  Tensor({{1, 0}, {0, 1}});
  // tensor 2x2x2
  Tensor({{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}});
  ```

- 기본 행 연산

  - $R_{i, j}$

  ```cpp
  swap_rows(matrix, 0, 1);
  ```

  - $R_{i}(c)$

  ```cpp
  scale_row(matrix, 0, 5);
  ```

  - $R_{i, j}(c)$

  ```cpp
  add_multiple_row(matrix, 0, 1, 5);
  ```

- 가우스 조던 소거법

  ```cpp
  matrix::solve(Tensor({{2, 1, -1, 8}, {0, 1, 1, 2}, {0, 0, -1, 1}}));
  // std::vector<double> {2, 3, -1}
  ```
