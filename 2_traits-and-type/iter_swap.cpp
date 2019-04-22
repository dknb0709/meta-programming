#include <algorithm>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <iostream>
#include <iterator>
#include <vector>

namespace dknb {

template <class Container>
void printAll(Container c) {
  std::copy(c.begin(), c.end(), std::ostream_iterator<int>(std::cout, " "));
  std::cout << std::endl;
}

template <bool use_swap>
struct iter_swap_impl;

template <class ForwardIterator1, class ForwardIterator2>
void iter_swap(ForwardIterator1 i1, ForwardIterator2 i2) {
  using traits1 = std::iterator_traits<ForwardIterator1>;
  using v1 = typename traits1::value_type;
  using r1 = typename traits1::reference;

  using traits2 = std::iterator_traits<ForwardIterator2>;
  using v2 = typename traits2::value_type;
  using r2 = typename traits2::reference;

  bool const use_swap = boost::is_same<v1, v2>::value &&
                        boost::is_reference<r1>::value &&
                        boost::is_reference<r2>::value;

  iter_swap_impl<use_swap>::do_it(i1, i2);
}

template <>
struct iter_swap_impl<true> {
  template <class ForwardIterator1, class ForwardIterator2>
  static void do_it(ForwardIterator1 i1, ForwardIterator2 i2) {
    typename std::iterator_traits<ForwardIterator1>::value_type tmp = *i1;
    *i1 = *i2;
    *i2 = tmp;
  }
};

template <>
struct iter_swap_impl<false> {
  template <class ForwardIterator1, class ForwardIterator2>
  static void do_it(ForwardIterator1 i1, ForwardIterator2 i2) {
    std::swap(*i1, *i2);
  }
};

}  // namespace dknb

int main() {
  std::vector<int> vec1{1, 2, 3, 4, 5};
  std::vector<int> vec2{6, 7, 8, 9, 10};
  dknb::printAll(vec1);
  dknb::printAll(vec2);
  dknb::iter_swap(vec1.begin(), vec2.begin());
  dknb::printAll(vec1);
  dknb::printAll(vec2);
}
