#include <initializer_list>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

class Tensor {
 private:
  std::vector<double> buffer;
  std::vector<int> shape;

  static bool is_same_dimension(const Tensor& t1, const Tensor& t2) {
    return t1.shape.size() == t2.shape.size();
  }

  bool is_scalar() const { return shape.size() == 0 && buffer.size() == 1; }
  bool is_matrix() const { return shape.size() == 2; }

 public:
  // scalar
  Tensor(const double& scalar) : buffer{scalar}, shape{} {}

  // tensor
  Tensor(const std::initializer_list<Tensor>& list) {
    if (list.size() == 0) {
      std::runtime_error("Void tensor is not allowed.");
    }

    // deep copy the shape of the first element
    auto it = list.begin();
    shape = it->shape;

    // check if the rest of the elements are the same
    for (; it != list.end(); it++) {
      if (it->shape != shape) {
        std::runtime_error("inconsistent tensor is not allowed.");
      }
    }

    // insert the current dimension size
    shape.insert(shape.begin(), list.size());

    // following code handles buffer
    for (const auto& element : list) {
      buffer.insert(buffer.end(), element.buffer.begin(), element.buffer.end());
    }
  }

  // when shape and buffer offered
  Tensor(const std::vector<int> input_shape, const std::vector<double> input_buffer) {
    buffer = input_buffer;
    shape = input_shape;
  }

  Tensor operator+(const Tensor& other) const {
    if (!is_same_dimension(*this, other)) {
      // TODO: change to compile time error
      std::runtime_error("Attempted addition between incompatible vector spaces.");
    }

    auto buffer_size = buffer.size();
    std::vector<double> result;
    result.reserve(buffer_size);
    for (int i = 0; i < buffer_size; i++) {
      result.push_back(buffer[i] + other.buffer[i]);
    }

    return Tensor(shape, result);
  }

  Tensor operator-(const Tensor& other) const {
    if (!is_same_dimension(*this, other)) {
      // TODO: change to compile time error
      std::runtime_error("Attempted addition between incompatible vector spaces.");
    }

    auto buffer_size = buffer.size();
    std::vector<double> result;
    result.reserve(buffer_size);
    for (int i = 0; i < buffer_size; i++) {
      result.push_back(buffer[i] - other.buffer[i]);
    }

    return Tensor(shape, result);
  }

  // handle scalar multiplication
  template <typename T, typename = std::is_arithmetic<T>>
  Tensor operator*(const T scalar) const {
    auto buffer_size = buffer.size();
    std::vector<double> result;
    result.reserve(buffer_size);
    for (int i = 0; i < buffer_size; i++) {
      result.push_back(buffer[i] * static_cast<double>(scalar));
    }

    return Tensor(shape, result);
  }

  Tensor operator*(const Tensor other) const {
    // handle scalar multiplication
    if (other.is_scalar()) {
      auto buffer_size = buffer.size();
      std::vector<double> result;
      result.reserve(buffer_size);
      auto scalar_value = other.buffer[0];
      for (int i = 0; i < buffer_size; i++) {
        result.push_back(buffer[i] * scalar_value);
      }

      return Tensor(shape, result);
    }

    // TODO: implement broadcasting multiplication
    if (!is_same_dimension(*this, other)) {
      std::runtime_error("broadcasting multiplication is not supported");
    }

    // handle element-wise multiplication
    auto buffer_size = buffer.size();
    std::vector<double> result;
    result.reserve(buffer_size);
    for (int i = 0; i < buffer_size; i++) {
      result.push_back(buffer[i] * other.buffer[i]);
    }

    return Tensor(shape, result);
  }

  // handle scalar divide
  template <typename T, typename = std::is_arithmetic<T>>
  Tensor operator/(const T scalar) {
    auto buffer_size = buffer.size();
    std::vector<double> result;
    result.reserve(buffer_size);
    for (int i = 0; i < buffer_size; i++) {
      result.push_back(buffer[i] / static_cast<double>(scalar));
    }

    return Tensor(shape, result);
  }

  Tensor operator/(const Tensor other) const {
    // handle scalar division
    if (other.is_scalar()) {
      auto buffer_size = buffer.size();
      std::vector<double> result;
      result.reserve(buffer_size);
      auto scalar_value = other.buffer[0];
      for (int i = 0; i < buffer_size; i++) {
        result.push_back(buffer[i] / scalar_value);
      }

      return Tensor(shape, result);
    }

    // TODO: implement broadcasting division
    if (!is_same_dimension(*this, other)) {
      std::runtime_error("broadcasting multiplication is not supported");
    }

    // handle element-wise division
    auto buffer_size = buffer.size();
    std::vector<double> result;
    result.reserve(buffer_size);
    for (int i = 0; i < buffer_size; i++) {
      // TODO: handle division with 0
      result.push_back(buffer[i] / other.buffer[i]);
    }

    return Tensor(shape, result);
  }

  // for debug
  void print() const {
    std::cout << "buffer: [ ";
    for (const auto& val : buffer) {
      std::cout << val << " ";
    }
    std::cout << "]\n";

    std::cout << "shape: [ ";
    for (const auto& val : shape) {
      std::cout << val << " ";
    }
    std::cout << "]" << std::endl;
  }
};
