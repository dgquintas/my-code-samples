#include <set>

using std::set;

int main() {
    set<int> s;

    auto comp = [](const int& a, const int& b) -> bool { return a > b;};
    set<int, decltype(comp)> t(comp);

    return 0;
}
