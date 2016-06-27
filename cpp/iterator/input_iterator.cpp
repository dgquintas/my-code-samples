#include <iostream>     // std::cout
#include <iterator>     // std::iterator, std::input_iterator_tag
#include <array>
#include <vector>
#include <algorithm>
#include <string>

typedef <typename T, size_t N>
class Ngram {
    public:
        Ngram(i...);

    private:
        std::array<T, N> arr_;
};


// Iterator (generator) over a vector of same-size arrays.
template <typename T, size_t N>
class MyIterator : public std::iterator<std::input_iterator_tag, T>
{
public:
  MyIterator(const std::vector<T>& v, int i) : v_{v}, i_{i} {}
  MyIterator(const MyIterator& mit) : v_(mit.v_), i_(mit.i_) {}
  MyIterator& operator++() {++i_; return *this;}
  MyIterator operator++(int) {MyIterator tmp(*this); operator++(); return tmp;}
  bool operator==(const MyIterator& rhs) {
      return (i_ == rhs.i_) && (v_ == rhs.v_);
  }
  bool operator!=(const MyIterator& rhs) {
      return !operator==(rhs);
  }
  std::array<T, N> operator*() {
      std::array<T, N> ret;
      if (i_ + N > v_.size()) {
         return ret;
      }
      const auto first = v_.begin() + i_;
      const auto last = first + N;
      std::copy(first, last, ret.begin());
      return ret;
  }

private:
  const std::vector<T>& v_;
  int i_;
};

template <typename T, size_t N>
void printNgram(const std::array<T, N>& arr) {
    std::cout << "[";
    for (const T& item : arr) {
        std::cout << item << ", ";
    }
    std::cout << "]\n";
}


int main () {
    const std::vector<std::string>
        v{"uno", "dos", "tres", "cuatro", "cinco", "seis"};
    constexpr size_t N = 2;
    MyIterator<std::string, N> beg(v, 0);
    MyIterator<std::string, N> end(v, v.size()-(N-1));

//    for (; beg != end; ++beg) {
//        printNgram(*beg);
//    }


    std::vector<std::array<std::string, N>> ngrams;
    std::copy(beg, end, std::back_inserter(ngrams));

    for (const auto& ngram : ngrams) {
        printNgram(ngram);
    }

    return 0;
}
