#include <initializer_list>
#include <iostream>

template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
class Tensor {
 private:
  // 여기에 데이터랑 텐서 모양 정의 관련 자료구조 넣기

  struct NestedTensor {
    NestedTensor(std::initializer_list<NestedTensor> list) {
      std::cout << "nested tensor's nested tensor called\n";
    }

    NestedTensor(std::initializer_list<T> list) {
      std::cout << "nested tensor scalar called\n";
    }

    // 여기에 데이터랑 텐서 모양 정의 관련 자료구조 넣기
  };

 public:
  // 스칼라
  Tensor(const int& scalar) {
    std::cout << "scalar constructor called\n";
    // data.push_back(static_cast<double>(scalar));
  }

  // 벡터
  Tensor(std::initializer_list<T>) {
    std::cout << "vector constructor called\n";
  }

  // n차원
  Tensor(std::initializer_list<NestedTensor>) {
    std::cout << "tensor constructor called\n";
  }
};

int main() {
  Tensor<int> a(5);                 // 스칼라
  Tensor<int> b({0, 1, 2});         // 벡터
  Tensor<int> c({{0, 1}, {1, 0}});  // 행렬
  Tensor<int> d({{{0, 1, 2}, {3, 4, 5}}, {{6, 7, 8}, {9, 10, 11}}});  // 텐서

  return 0;
}
