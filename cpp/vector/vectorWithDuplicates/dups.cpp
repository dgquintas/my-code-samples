#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>

int main(){
  int tmp[] = { 2,3,2,3,3,3,8,9,10 };
  std::vector<int> v(tmp,tmp+9);

  std::sort(v.begin(), v.end());

  for(int i = 0 ; i < v.size(); i++){
    std::cout << v[i] << std::endl;
  }


  std::vector< std::pair<int, int> > v2;
  
  for(int i = 0 ; i < v.size(); ){
    int current = v[i];
    int count = 1;
    while( (++i < v.size()) && (v[i] == current) ){
      count++;
    }
    v2.push_back( std::pair<int, int>(current, count) );
  }

  for(int i = 0 ; i < v2.size(); i++){
    std::cout << "(" << v2[i].first << ", " << v2[i].second << ")" << std::endl;
  }




  return 0;
}

