#include <initializer_list>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <vector>

class Tensor {
 private:
  std::vector<double> buffer;
  std::vector<int> shape;

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
    if (other.shape != this->shape) {
      // TODO: change to compile time error
      std::runtime_error("Attempted addition between incompatible vector spaces.");
    }

    auto buffer_size = buffer.size();
    std::vector<double> result;
    result.reserve(buffer_size);
    for (int i = 0; i < buffer_size; i++) {
      result.push_back(other.buffer[i] + buffer[i]);
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
