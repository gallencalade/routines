#include <getopt.h>

#include <iostream>
#include <string>
#include <fstream>
#include <streambuf>

using namespace std;

void help() {
  std::cout << std::endl;
  std::cout << "\tUsage: longopt <option> <param> ...\n"
               "\t\t--option A, -a\tOption A.\n"
               "\t\t--option B, -b\tOption B.\n"
               "\t\t--option C, -c\tOption C.\n"
               "\t\t--option D, -d\tOption D.\n"
            << std::endl;
}

bool check_arg(int argc, char* argv[]) {
  return true;
}

int main(int argc, char* argv[]) {
  if (!check_arg(argc, argv)) {
    help();
    return -1;
  }

  const char* const shot_opts = "a:b:cd";
  struct option long_opts[] = {
    { "opta", 1, nullptr, 'a' },
    { "optb", 1, nullptr, 'b' },
    { "optc", 0, nullptr, 'c' },
    { "optd", 0, nullptr, 'd' },
    { nullptr, 0, nullptr, 0 },
  };

  std::string arg_a;
  std::string arg_b;
  bool arg_c = false;
  bool arg_d = false;
  char opt;
  while (-1 != (opt = getopt_long(argc, argv, shot_opts, long_opts, nullptr))) {
    switch (opt) {
      case 'a':
        arg_a.assign(optarg);
        break;
      case 'b':
        arg_b.assign(optarg);
        break;
      case 'c':
        arg_c = true;
        break;
      case 'd':
        arg_d = true;
        break;
      default:
        help();
        return -1;
    }
  }

  std::cout << "Arg of option a is " << (arg_a.empty() ? "[empty]" : arg_a) << std::endl;
  std::cout << "Arg of option b is " << (arg_b.empty() ? "[empty]" : arg_b) << std::endl;
  std::cout << "Arg of option c is " << (arg_c ? "set" : "unset") << std::endl;
  std::cout << "Arg of option d is " << (arg_d ? "set" : "unset") << std::endl;

  return 0;
}
