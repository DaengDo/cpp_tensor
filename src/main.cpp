#include <initializer_list>
#include <iostream>
#include <vector>

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

int main() {
  Tensor a(5);  // scalar
  a.print();

  std::cout << "---------------------\n";

  Tensor b({0, 1, 2});  // vector
  b.print();

  std::cout << "---------------------\n";

  Tensor c({{0, 1}, {1, 0}});  // matrix
  c.print();

  std::cout << "---------------------\n";

  Tensor d({{{0, 1, 2}, {3, 4, 5}}, {{6, 7, 8}, {9, 10, 11}}});  // tensor
  d.print();

  std::cout << "---------------------\n";

  return 0;
}
