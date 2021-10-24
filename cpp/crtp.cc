#include <iostream>
#include <string>

namespace base {

template <typename T>
struct Base {
  void Interface() final {
    auto& d = static_cast<T&>(*this);
    d.Implement();
  }
};

struct Derived : public Base<Derived> {
  void Implement() {
    std::cout << "Derived::Implement" << std::endl;
  }
};

}   // namespace base

namespace multi_base {

template <typename T>
struct BaseA {
  void InterfaceA() {
    auto& d = static_cast<T&>(*this);
    d.Implement();
  }
};

template <typename T>
struct BaseB : public BaseA<T> {
  void InterfaceB() {
    auto& d = static_cast<T&>(*this);
    d.Implement();
  }
};

struct Derived : public BaseB<Derived> {
  void Implement() {
    std::cout << "Derived::Implement" << std::endl;
  }
};

}   // namespace multi_base

namespace level_base {

template <typename T>
struct BaseA {
  void InterfaceA() {
    auto& d = static_cast<T&>(*this);
    d.Implement();
  }
};

template <typename T>
struct BaseB {
  void InterfaceB() {
    auto& d = static_cast<T&>(*this);
    d.Implement();
  }
};

template <template <typename> typename... T>
struct Derived : public T<Derived<T...>>... {
  void Implement() {
    std::cout << "Derived::Implement" << std::endl;
  }
};

}   // namespace level_base
int main() {
  {
  base::Derived d;
  d.Interface();
  }

  {
  multi_base::Derived d;
  d.InterfaceA();
  d.InterfaceB();
  }

  {
  level_base::Derived<level_base::BaseA, level_base::BaseB> d;
  d.InterfaceA();
  d.InterfaceB();
  }
}
