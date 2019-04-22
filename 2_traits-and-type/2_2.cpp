#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <cassert>

struct A {
  virtual ~A() {}
};

struct B : A {};

template <class Target, class Source>
inline Target polymorphic_downcast(Source* x) {
  assert(dynamic_cast<Target>(x) == x);
  return static_cast<Target>(x);
}

template <class Target, class Source>
inline Target polymorphic_downcast(Source& x) {
  assert(dynamic_cast<typename boost::add_pointer<
             typename boost::remove_reference<Source>::type>::type>(&x) == &x);
  return static_cast<Target>(x);
}

int main() {
  // run tests
  B b;
  A* a_ptr = &b;
  B* b_ptr = polymorphic_downcast<B*>(a_ptr);

  A& a_ref = b;
  B& b_ref = polymorphic_downcast<B&>(a_ref);
}
