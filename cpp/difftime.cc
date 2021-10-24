#include <iostream>

int main(int argc, char* argv[]) {
  tm tm_in = { 0 };
  if (nullptr == strptime(argv[1], "%Y-%m-%d", &tm_in)) {
    std::cerr << "Failed to strptime from input" << std::endl;
    return -1;
  }
  time_t time_in = mktime(&tm_in);

  time_t time_now = time(nullptr);
  if (difftime(time_in, time_now) > 0) {
    std::cout << "Inputed time is larger than time now" << std::endl;
  } else {
    std::cout << "Inputed time is less than time now" << std::endl;
  }

  return 0;
}
