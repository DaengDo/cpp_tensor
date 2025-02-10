#pragma once

#include <stdexcept>
#include <vector>

#include "../tensor/tensor.h"

namespace matrix {
void assert_matrix(Tensor matrix, const char* err_msg);

// elementary row operation
// R { i, j }
Tensor swap_rows(Tensor matrix, size_t row_i, size_t row_j);
// R { i } * c
Tensor scale_row(Tensor matrix, size_t row_i, double scalar_c);
// R { i, j } * c
Tensor add_multiple_row(Tensor matrix, size_t row_i, size_t row_j, double scalar_c);

std::vector<size_t> find_zero_rows(Tensor matrix);
bool is_reduced_row_echoelon_form(Tensor matrix);

// Gauss-Jordan elimination
std::vector<double> solve(Tensor matrix);
}  // namespace matrix
