#pragma once

#include <stdexcept>
#include <vector>

#include "../tensor/tensor.h"

namespace matrix {
void assert_matrix(Tensor matrix, const char* err_msg);

// elementary row operation
// R_{i, j}
auto swap_rows(Tensor matrix, size_t row_i, size_t row_j) -> Tensor;
// R_i(c)
auto scale_row(Tensor matrix, size_t row_i, double scalar_c) -> Tensor;
// R_{i, j}(c)
auto add_multiple_row(Tensor matrix, size_t row_i, size_t row_j, double scalar_c) -> Tensor;

auto find_zero_rows(Tensor matrix) -> std::vector<size_t>;
auto is_reduced_row_echoelon_form(Tensor matrix) -> bool;

// Gauss-Jordan elimination
auto solve(Tensor matrix) -> std::vector<double>;

auto multiplication(Tensor left, Tensor right) -> Tensor;

auto transpose(Tensor matrix) -> Tensor;

// 행렬 A에 대해 A^T == A 를 만족하는지 여부
auto is_symmetric(Tensor a, Tensor b) -> bool;
}  // namespace matrix
