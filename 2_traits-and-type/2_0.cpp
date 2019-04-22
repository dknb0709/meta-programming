#include <boost/type_traits/is_same.hpp>
#include <iostream>

void test(const char* msg, bool isOk) {
  std::cout << msg << ": " << (isOk ? "OK" : "NG") << std::endl;
}

template <class T>
struct add_const_ref {
  using type = const T&;
};

template <class T>
struct add_const_ref<T&> {
  using type = T&;
};

int main() {
  using v1 = add_const_ref<int>::type;
  test("int", boost::is_same<v1, const int&>::value);
  using v2 = add_const_ref<int&>::type;
  test("int&", boost::is_same<v2, int&>::value);
  using v3 = add_const_ref<const int&>::type;
  test("const int&", boost::is_same<v3, const int&>::value);
}
