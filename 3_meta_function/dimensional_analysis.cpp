#include <boost/mpl/equal.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector_c.hpp>
#include <boost/static_assert.hpp>
#include <iostream>

namespace mpl = boost::mpl;
using namespace mpl::placeholders;

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

  template <class OtherDimensions>
  quantity(quantity<T, OtherDimensions> const& rhs) : m_value(rhs.value()) {
    BOOST_STATIC_ASSERT((mpl::equal<Dimensions, OtherDimensions>::type::value));
  }

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

// operator *
template <class T, class D1, class D2>
quantity<T, typename mpl::transform<D1, D2, plus_f>::type> operator*(
    quantity<T, D1> x, quantity<T, D2> y) {
  using dim = typename mpl::transform<D1, D2, plus_f>::type;
  return quantity<T, dim>(x.value() * y.value());
}

// typedef typename mpl::minus<T1, T2>::type is not
// necessary anymore, by using inheritance
// this powerfull simplification is called
// "metafunction forwarding"
struct minus_f {
  template <class T1, class T2>
  struct apply : mpl::minus<T1, T2> {};
};

// operator /
template <class T, class D1, class D2>
quantity<T, typename mpl::transform<D1, D2, mpl::minus<_1, _2>>::type>
operator/(quantity<T, D1> x, quantity<T, D2> y) {
  using dim = typename mpl::transform<D1, D2, mpl::minus<_1, _2>>::type;
  return quantity<T, dim>(x.value() / y.value());
}

int main() {
  quantity<float, mass> m(5.0f);
  quantity<float, acceleration> a(9.8f);

  quantity<float, force> f = m * a;
  std::cout << "force = " << f.value() << std::endl;

  quantity<float, mass> m2 = f / a;
  std::cout << "mass = " << m2.value() << std::endl;
  std::cout << "rounding error = " << std::abs((m2 - m).value()) << std::endl;
}
