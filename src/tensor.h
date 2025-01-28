#include <initializer_list>
#include <iostream>
#include <vector>

namespace detail {
template <size_t Dim = 0>
class Tensor {
 private:
  std::vector<double> buffer;

  // Helper function to print the tensor
  void printImpl(const std::vector<double>& vec) const {
    std::cout << "[ ";
    for (const auto& val : vec) {
      std::cout << val << " ";
    }
    std::cout << "]" << std::endl;
  }

 public:
  // scalar
  Tensor(const double& scalar) {
    buffer.push_back(static_cast<double>(scalar));
  }

  // tensor
  Tensor(const std::initializer_list<Tensor>& list) {
    for (const auto& element : list) {
      buffer.insert(buffer.end(), element.buffer.begin(), element.buffer.end());
    }
  }

  // Print the tensor
  void print() const { printImpl(buffer); }
};
}  // namespace detail

using Tensor = detail::Tensor<>;
