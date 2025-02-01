#pragma once

#include <stdexcept>

#include "tensor.h"

namespace matrix {
// elementary row operation

// R { i, j }
Tensor swap_rows(Tensor matrix, size_t row_i, size_t row_j) {
  if (!matrix.is_matrix()) {
    std::runtime_error("elementary row operation(swap row) can only be applied to matrix");
  };

  auto buffer = matrix.get_buffer();
  auto shape = matrix.get_shape();

  auto row_size = shape[0];
  auto col_size = shape[1];

  if (row_i > row_size - 1 || row_j > row_size - 1) {
    std::runtime_error("selection of not existed row");
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
  if (!matrix.is_matrix()) {
    std::runtime_error("elementary row operation(scale row) can only be applied to matrix");
  };

  auto buffer = matrix.get_buffer();
  auto shape = matrix.get_shape();

  auto row_size = shape[0];
  auto col_size = shape[1];

  if (row_i > row_size - 1) {
    std::runtime_error("selection of not existed row");
  }

  for (int i = 0; i < col_size; i++) {
    buffer[i + row_i * col_size] *= scalar_c;
  }

  return Tensor(shape, buffer);
}

// R { i, j } * c
Tensor add_muliple_row(Tensor matrix, size_t row_i, size_t row_j, double scalar_c) {
  if (!matrix.is_matrix()) {
    std::runtime_error("elementary row operation(add multiple row) can only be applied to matrix");
  };

  auto buffer = matrix.get_buffer();
  auto shape = matrix.get_shape();

  auto row_size = shape[0];
  auto col_size = shape[1];

  if (row_i > row_size - 1 || row_j > row_size - 1) {
    std::runtime_error("selection of not existed row");
  }

  for (int i = 0; i < col_size; i++) {
    buffer[i + row_j * col_size] += scalar_c * buffer[i + row_i * col_size];
  }

  return Tensor(shape, buffer);
}

}  // namespace matrix
