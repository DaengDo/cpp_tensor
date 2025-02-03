#pragma once

#include <stdexcept>
#include <vector>

#include "tensor.h"

namespace matrix {
// TODO: change to compile time error
void assert_matrix(Tensor matrix, const char* err_msg) {
  if (matrix.is_matrix()) return;
  throw std::runtime_error(err_msg);
}

// elementary row operation

// R { i, j }
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

// R { i } * c
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

// R { i, j } * c
Tensor add_muliple_row(Tensor matrix, size_t row_i, size_t row_j, double scalar_c) {
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
    for (int col = 0; col < col_size; col++) {
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

std::vector<double> solve() {
  // TODO: 가우스 조던 소거법으로 연립일차방정식 풀기
  return std::vector<double>{};
}

}  // namespace matrix
