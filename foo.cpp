#include <jlcxx/jlcxx.hpp>
#include <jlcxx/stl.hpp>

class Foo {
private:
  int m_value;

public:
  Foo(int l = 0) : m_value{l} {}
  int add(int L) const { return m_value + L; }
  Foo *thisptr() { return this; }
  Foo &thisref() { return *this; }
  Foo thiscopy() { return *this; }
  const int *valueptr() { return &m_value; }
};

JLCXX_MODULE define_julia_module(jlcxx::Module &mod) {
  mod.add_type<Foo>("Foo")
      .constructor<int>()
      .method("add", &Foo::add)
      .method("thisptr", &Foo::thisptr)
      .method("thisref", &Foo::thisref)
      .method("thiscopy", &Foo::thiscopy)
      .method("valueptr", &Foo::valueptr);
  mod.method("sumfoos", [](const std::vector<Foo> &vec) {
    int result = 0;
    for (auto foo : vec) {
      result += *foo.valueptr();
    }
    return result;
  });
}
