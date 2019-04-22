#include <boost/mpl/print.hpp>
#include <iostream>

template <typename T>
struct type_descriptor {};

template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor<T&> const&) {
  os << type_descriptor<T>() << "への参照";
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor<T*> const&) {
  os << type_descriptor<T>() << "へのポインタ";
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor<T const> const&) {
  os << type_descriptor<T>() << "定数";
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor<T[]> const&) {
  os << type_descriptor<T>() << "配列";
  return os;
}

template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, type_descriptor<T[N]> const&) {
  os << "要素数" << N << "の" << type_descriptor<T>() << "配列";
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor<T()> const&) {
  os << type_descriptor<T>() << "を返す関数";
  return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, type_descriptor<T (*)()> const&) {
  os << type_descriptor<T>() << "を返す関数へのポインタ";
  return os;
}

std::ostream& operator<<(std::ostream& os, type_descriptor<char> const&) {
  os << "char";
  return os;
}

std::ostream& operator<<(std::ostream& os, type_descriptor<short> const&) {
  os << "short";
  return os;
}

std::ostream& operator<<(std::ostream& os, type_descriptor<int> const&) {
  os << "int";
  return os;
}

std::ostream& operator<<(std::ostream& os, type_descriptor<long> const&) {
  os << "long";
  return os;
}

std::ostream& operator<<(std::ostream& os, type_descriptor<long long> const&) {
  os << "long long";
  return os;
}

int main() {
  // run tests
  std::cout << type_descriptor<int const&>() << std::endl;
  std::cout << type_descriptor<const int&>() << std::endl;
  std::cout << type_descriptor<int* const>() << std::endl;
  std::cout << type_descriptor<int const*>() << std::endl;
  std::cout << type_descriptor<int()>() << std::endl;
  std::cout << type_descriptor<short[5]>() << std::endl;
  std::cout << type_descriptor<const long*>() << std::endl;
  std::cout << type_descriptor<char* (*[])()>() << std::endl;
}
