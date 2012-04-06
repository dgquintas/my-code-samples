#include <vector>
#include <algorithm>

using namespace std;
int main()
{
  vector<int> v;

  v.erase( remove(v.begin(), v.end(), 0), v.end());

  return 0;
}
