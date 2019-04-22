#include <boost/mpl/print.hpp>
#include <iostream>

template <typename T>
struct type_discriptor {};

template <typename T>
std::ostream& operator<<(std::ostream& os, type_discriptor<T&> const&) {
  os << type_discriptor<T>() << "&";
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, type_discriptor<T*> const&) {
  os << type_discriptor<T>() << "*";
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, type_discriptor<T const> const&) {
  os << type_discriptor<T>() << " const";
  return os;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, type_discriptor<T[N]> const&) {
  os << type_discriptor<T>() << "[" << N << "]";
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, type_discriptor<T()> const&) {
  os << type_discriptor<T>() << "()";
  return os;
}

std::ostream& operator<<(std::ostream& os, type_discriptor<char> const&) {
  os << "char";
  return os;
}

std::ostream& operator<<(std::ostream& os, type_discriptor<short> const&) {
  os << "short";
  return os;
}

std::ostream& operator<<(std::ostream& os, type_discriptor<int> const&) {
  os << "int";
  return os;
}

std::ostream& operator<<(std::ostream& os, type_discriptor<long> const&) {
  os << "long";
  return os;
}

std::ostream& operator<<(std::ostream& os, type_discriptor<long long> const&) {
  os << "long long";
  return os;
}

int main() {
  // run tests
  std::cout << type_discriptor<int const&>() << std::endl;
  std::cout << type_discriptor<const int&>() << std::endl;
  std::cout << type_discriptor<int* const>() << std::endl;
  std::cout << type_discriptor<int()>() << std::endl;
  std::cout << type_discriptor<short[5]>() << std::endl;
}
