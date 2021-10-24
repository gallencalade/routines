#include <utility>
#include <iostream>

template <std::size_t... N>
auto indexes_multi(std::index_sequence<N...>) -> std::index_sequence<(2 * N)...>;

template<typename T, T... ints>
void print_sequence(std::integer_sequence<T, ints...> int_seq)
{
      std::cout << "The sequence of size " << int_seq.size() << ": ";
          ((std::cout << ints << ' '),...);
              std::cout << '\n';
}

int main() {
  decltype(indexes_multi(std::make_index_sequence<10>{})) test;
  print_sequence(test);
}
