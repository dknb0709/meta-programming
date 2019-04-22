#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector_c.hpp>
#include <iostream>

namespace mpl = boost::mpl;

using mass = mpl::vector_c<int, 1, 0, 0, 0, 0, 0, 0>;
using length = mpl::vector_c<int, 0, 1, 0, 0, 0, 0, 0>;
using time_ = mpl::vector_c<int, 0, 0, 1, 0, 0, 0, 0>;
using charge = mpl::vector_c<int, 0, 0, 0, 1, 0, 0, 0>;
using temperature = mpl::vector_c<int, 0, 0, 0, 0, 1, 0, 0>;
using intensity = mpl::vector_c<int, 0, 0, 0, 0, 0, 1, 0>;
using amount_of_substance = mpl::vector_c<int, 0, 0, 0, 0, 0, 0, 1>;

using velocity = mpl::vector_c<int, 0, 1, -1, 0, 0, 0, 0>;
using acceleration = mpl::vector_c<int, 0, 1, -2, 0, 0, 0, 0>;
using force = mpl::vector_c<int, 1, 1, -2, 0, 0, 0, 0>;

template <class T, class Dimensions>
struct quantity {
  explicit quantity(T x) : m_value(x) {}
  T value() const { return m_value; }

 private:
  T m_value;
};

// operator +
template <class T, class D>
quantity<T, D> operator+(quantity<T, D> x, quantity<T, D> y) {
  return quantity<T, D>(x.value() + y.value());
}

// operator -
template <class T, class D>
quantity<T, D> operator-(quantity<T, D> x, quantity<T, D> y) {
  return quantity<T, D>(x.value() - y.value());
}

//----------------------------
// operator *, /
//----------------------------
struct plus_f {
  template <class T1, class T2>
  struct apply {
    using type = typename mpl::plus<T1, T2>::type;
  };
};

template <class T, class D1, class D2>
quantity<T, typename mpl::transform<D1, D2, plus_f>::type> operator*(
    quantity<T, D1> x, quantity<T, D2> y) {
  using dim = typename mpl::transform<D1, D2, plus_f>::type;
  return quantity<T, dim>(x.value() * y.value());
}

int main() {
  quantity<float, mass> m(5.0f);
  quantity<float, acceleration> a(9.8f);

  std::cout << (m * a).value() << std::endl;
}
