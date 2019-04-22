#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <iostream>

void test(const char* msg, bool isOk) {
  std::cout << msg << ": " << (isOk ? "OK" : "NG") << std::endl;
}

template <class C, class X, class Y, bool isSame>
struct replace_type_dispatch {};

template <class C, class X, class Y>
struct replace_type {
  using type =
      typename replace_type_dispatch<C, X, Y,
                                     boost::is_same<C, X>::value>::type;
};

template <class C, class X, class Y>
struct replace_type<C*, X, Y> {
  using type = typename boost::add_pointer<typename replace_type_dispatch<
      C, X, Y, boost::is_same<C, X>::value>::type>::type;
};

template <class C, class X, class Y>
struct replace_type<C&, X, Y> {
  using type = typename boost::add_reference<typename replace_type_dispatch<
      C, X, Y, boost::is_same<C, X>::value>::type>::type;
};

template <class C, class X, class Y, size_t N>
struct replace_type<C[N], X, Y> {
  using type = typename boost::add_reference<typename replace_type_dispatch<
      C, X, Y, boost::is_same<C, X>::value>::type>::type[N];
};

template <class Cr, class X, class Y>
struct replace_type<Cr (*)(), X, Y> {
  typedef typename replace_type_dispatch<
      Cr, X, Y, boost::is_same<Cr, X>::value>::type (*type)();
};

template <class Cr, class C0, class X, class Y>
struct replace_type<Cr (*)(C0), X, Y> {
  typedef
      typename replace_type_dispatch<Cr, X, Y, boost::is_same<Cr, X>::value>::
          type (*type)(typename replace_type_dispatch<
                       C0, X, Y, boost::is_same<C0, X>::value>::type);
};

template <class Cr, class C0, class C1, class X, class Y>
struct replace_type<Cr (*)(C0, C1), X, Y> {
  typedef
      typename replace_type_dispatch<Cr, X, Y, boost::is_same<Cr, X>::value>::
          type (*type)(typename replace_type_dispatch<
                           C0, X, Y, boost::is_same<C0, X>::value>::type,
                       typename replace_type_dispatch<
                           C1, X, Y, boost::is_same<C1, X>::value>::type);
};

template <class C, class X, class Y>
struct replace_type_dispatch<C, X, Y, true> {
  using type = Y;
};

template <class C, class X, class Y>
struct replace_type_dispatch<C, X, Y, false> {
  using type = typename replace_type<C, X, Y>::type;
};

int main() {
  // run tests
  using t1 = replace_type<int&, int, long>::type;
  test("long&", boost::is_same<t1, long&>::value);
  using t2 = replace_type<int, int, long>::type;
  test("long", boost::is_same<t2, long>::value);
  using t3 = replace_type<char& (*)(char&), char&, long&>::type;
  test("long&(*)(long&)", boost::is_same<t3, long& (*)(long&)>::value);
  using t4 = replace_type<void*, void, int>::type;
  test("int*", boost::is_same<t4, int*>::value);

}
