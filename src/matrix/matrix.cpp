#include "matrix.h"

#include <cmath>
#include <stdexcept>
#include <vector>

namespace matrix {
// TODO: change to compile time error
void assert_matrix(Tensor matrix, const char* err_msg) {
  if (matrix.is_matrix()) return;
  throw std::runtime_error(err_msg);
}

// R_{i, j}
Tensor swap_rows(Tensor matrix, size_t row_i, size_t row_j) {
  assert_matrix(matrix, "elementary row operation(swap row) can only be applied to matrix");

  auto buffer = matrix.get_buffer();
  auto shape = matrix.get_shape();

  auto row_size = shape[0];
  auto col_size = shape[1];

  if (row_i > row_size - 1 || row_j > row_size - 1) {
    throw std::runtime_error("selection of not existed row");
  }

  // 예를 들어 3 x 2 행렬에서 0, 2을 변경한다면
  // buffer의 0,1 과 4,5를 swap 해야 함
  // for문 돌릴 때 col 갯수만큼 반복하되, i와 j더한 인덱스를 서로 교환
  for (int i = 0; i < col_size; i++) {
    auto temp = buffer[i + row_i * col_size];
    buffer[i + row_i * col_size] = buffer[i + row_j * col_size];
    buffer[i + row_j * col_size] = temp;
  }

  return Tensor(shape, buffer);
}

// R_i(c)
Tensor scale_row(Tensor matrix, size_t row_i, double scalar_c) {
  assert_matrix(matrix, "elementary row operation(scale row) can only be applied to matrix");

  auto buffer = matrix.get_buffer();
  auto shape = matrix.get_shape();

  auto row_size = shape[0];
  auto col_size = shape[1];

  if (row_i > row_size - 1) {
    throw std::runtime_error("selection of not existed row");
  }

  for (int i = 0; i < col_size; i++) {
    buffer[i + row_i * col_size] *= scalar_c;
  }

  return Tensor(shape, buffer);
}

// R_{i, j}(c)
Tensor add_multiple_row(Tensor matrix, size_t row_i, size_t row_j, double scalar_c) {
  assert_matrix(matrix, "elementary row operation(add multiple row) can only be applied to matrix");

  auto buffer = matrix.get_buffer();
  auto shape = matrix.get_shape();

  auto row_size = shape[0];
  auto col_size = shape[1];

  if (row_i > row_size - 1 || row_j > row_size - 1) {
    throw std::runtime_error("selection of not existed row");
  }

  for (int i = 0; i < col_size; i++) {
    buffer[i + row_j * col_size] += scalar_c * buffer[i + row_i * col_size];
  }

  return Tensor(shape, buffer);
}

std::vector<size_t> find_zero_rows(Tensor matrix) {
  auto shape = matrix.get_shape();
  auto row_size = shape[0];
  auto buffer = matrix.get_buffer();
  auto col_size = shape[1];
  std::vector<size_t> zero_row_indices;

  for (int row = 0; row < row_size - 1; row++) {
    bool is_zero_row = true;

    for (int i = 0; i < col_size; i++) {
      auto element = buffer[i + row * col_size];

      if (element != 0) {
        is_zero_row = false;
        break;
      }
    }

    if (is_zero_row) zero_row_indices.push_back(row);
  }

  return zero_row_indices;
}

bool is_reduced_row_echoelon_form(Tensor matrix) {
  assert_matrix(matrix, "elementary row operation(add multiple row) can only be applied to matrix");

  size_t zero_row_anchor = 0;

  for (auto zero_row_idx : find_zero_rows(matrix)) {
    if (zero_row_idx == 0) continue;
    // 영행 아래에 영행 아닌 행이 있다면 RREF가 아니다
    if (zero_row_idx < zero_row_anchor) return false;
  }

  auto buffer = matrix.get_buffer();
  auto shape = matrix.get_shape();
  auto row_size = shape[0];
  auto col_size = shape[1];

  int upper_leading_entry_anchor = -1;

  for (int row = 0; row < row_size; row++) {
    bool has_leading_entry = false;
    for (int col = 0; col < col_size - 1; col++) {
      auto element = buffer[col + row * col_size];

      if (element == 0) continue;
      if (element != 1) return false;
      // 이하 element가 1인 경우

      // 위쪽 행의 선도원소가 더 오른쪽에 있으면 RREF가 아니다
      if (upper_leading_entry_anchor >= col) return false;

      // 선도원소 외의 요소가 0이 아니라면 RREF가 아니다
      if (has_leading_entry) return false;

      // 선도원소가 맞는 경우
      upper_leading_entry_anchor = col;
      has_leading_entry = true;
    }
  };

  return true;
}

std::vector<double> solve(Tensor matrix) {
  assert_matrix(matrix, "Gauss-Jordan elimination can only compatible with matrix");

  auto buffer = matrix.get_buffer();
  auto shape = matrix.get_shape();

  auto row_size = shape[0];
  auto col_size = shape[1];

  // TODO: rank와 관련 없는 행(ex: 무의미한 영행) 지우기

  // 미지수 갯수와 일차식 갯수가 같은지 확인
  if (row_size != (col_size - 1)) return std::vector<double>{};

  // 1. make REF(row echolon form)
  for (size_t row = 0; row < row_size; row++) {
    for (size_t col = 0; col < col_size - 1; col++) {
      auto element = buffer[col + row * col_size];

      if (col < row) {
        // 1) 선도원소 앞 요소인 경우
        if (element == 0) continue;

        // 0으로 만들기 위해 이전 행의 선도원소로 R_{i, j}(c) 하기
        matrix = add_multiple_row(matrix, col, row, -element);
        buffer = matrix.get_buffer();
      } else if (col > row) {
        // 2) 선도원소보다 뒤 요소인 경우
        continue;
      } else {
        // 3) 선도원소인 경우
        if (element == 0) {
          // 기본 행 연산으로 가장 큰 행 찾아서 변환하기
          size_t biggest_row = row;
          double biggest_leading = element;

          // 현재 행의 leading과 다른 모든 leading 비교
          for (int k = 0; k < row_size - 1; k++) {
            double leading = buffer[col + k * col_size];

            if (leading > std::abs(biggest_leading)) {
              biggest_leading = leading;
              biggest_row = k;
            }
          }
          matrix = swap_rows(matrix, row, biggest_row);
          buffer = matrix.get_buffer();
          element = buffer[col + row * col_size];
        }

        // 선도원소를 1로 만들어주기
        matrix = scale_row(matrix, row, 1 / element);
        buffer = matrix.get_buffer();
      }
    }
  }

  std::vector<double> result;
  result.reserve(row_size);

  // 2. make RREF
  for (size_t row = 0; row < row_size; row++) {
    for (size_t col = 0; col < col_size; col++) {
      // 이미 REF 이므로, 선도 원소보다 뒤의 요소만 다뤄, RREF로 만들기
      bool is_prev_leading = col < row;
      bool is_leading = col == row;
      if (is_prev_leading || is_leading) continue;

      bool is_const_element = col == row_size;  // 상수열은 해로 저장하기
      if (is_const_element) {
        result.push_back(buffer[col + row * col_size]);
      } else {
        // 아래쪽의 선도원소 찾아서 R_{i, j}(c) 해주기
        auto element = buffer[col + row * col_size];
        matrix = add_multiple_row(matrix, col, row, -element);
        buffer = matrix.get_buffer();
      }
    }
  }

  return result;
}

Tensor multiplication(Tensor left, Tensor right) {
  assert_matrix(left, "the left operand of the matrix multiplication is not a matrix.");
  assert_matrix(right, "the right operand of the matrix multiplication is not a matrix.");

  auto left_buffer = left.get_buffer();
  auto right_buffer = right.get_buffer();

  auto left_shape = left.get_shape();    // m x i
  auto right_shape = right.get_shape();  // i x n

  size_t m, i, n;  // m x n 형태의 행렬을 반환하기 위한 변수 선언

  if (left_shape.size() == 1) {
    m = 1;
    i = left_shape[0];
  } else {
    m = left_shape[0];
    i = left_shape[1];
  }

  if (right_shape.size() == 1) {
    i = 1;
    n = right_shape[0];
  } else {
    i = right_shape[0];
    n = right_shape[1];
  }

  std::vector<double> buffer;
  buffer.reserve(m * n);

  // c_{m_n} = \sum_{k=1}^(n)  (a_{m_k}) * (b_{k_n})
  for (size_t row = 0; row < m; row++) {
    for (size_t col = 0; col < n; col++) {
      size_t result = 0;
      double sum = 0;

      for (size_t k = 0; k < i; k++) {
        auto left_element = left_buffer[i * row + k];
        auto right_element = right_buffer[k * n + col];
        sum += left_element * right_element;
      }

      buffer.push_back(sum);
    }
  }

  // TODO: Tensor 클래스가 벡터일 때 1 x n 형태를 자동 지원하도록 개선하기
  if (m == 1 && m == n) {
    return Tensor(std::vector<size_t>{1}, buffer);
  } else {
    return Tensor(std::vector<size_t>{m, n}, buffer);
  }
}
}  // namespace matrix
