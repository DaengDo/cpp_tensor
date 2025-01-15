#include <concepts>
#include <initializer_list>
#include <iostream>
#include <vector>

class Tensor {
 public:
  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int> ||
                                                    std::is_same_v<T, double>>>
  Tensor(T value) {
    this->data.push_back(static_cast<double>(value));
  }

  template <typename T, typename = std::enable_if_t<std::is_same_v<T, int> ||
                                                    std::is_same_v<T, double>>>
  Tensor(std::initializer_list<T> list) {
    if (list.size() == 0) {
      this->data.push_back(0.0);
      return;
    }
    for (const auto& elem : list) {
      this->data.push_back(static_cast<double>(elem));
    }
  }

 private:
  std::vector<int> stride = {};
  std::vector<int> shape = {};
  std::vector<double> data = {};
};

int main() {
  Tensor myScalar1 = Tensor(0.3);
  Tensor myScalar2 = Tensor({0, 1, 2, 3});

  return 0;
}
