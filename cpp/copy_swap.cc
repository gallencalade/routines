#include <algorithm>    // std::copy
#include <cstdint>      // std::size_t
#include <cstring>      // std::strlen

#include <iostream>

class String{
 public:
  explicit String(const char* p)
      : size_(std::strlen(p))
      , buf_(0 != size_ ? new char[size_] : nullptr) {
      std::copy(p, p + size_, buf_);
  };

  String(const String& oth)
      : size_(oth.size_)
      , buf_(0 != size_ ? new char[size_] : nullptr) {
    std::copy(oth.buf_, oth.buf_ + size_, buf_);
  }

  String& operator=(String oth) {
    Swap(*this, oth);

    return *this;
  }

  void Swap(String& lhs, String& rhs) noexcept {
    std::swap(lhs.buf_, rhs.buf_);
    std::swap(lhs.size_, rhs.size_);
  }

  ~String() {
    delete[] buf_;
    buf_ = nullptr;
    size_ = 0;
  }

  const char* buf() const { return buf_; }

 private:
  std::size_t size_;
  char* buf_;
};

int main() {
  String s("adsfadsfasdf");
  std::cout << s.buf() << std::endl;
  String s1("14324");
  std::cout << s1.buf() << std::endl;
  s1 = s;
  std::cout << s1.buf() << std::endl;
  String s2(s1);
  std::cout << s2.buf() << std::endl;
}
