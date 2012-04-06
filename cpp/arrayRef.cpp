int main(){

  int* v = new int[3];

  v[0] = 1;
  v[1] = 2;
  v[2] = 3;

  int noref = v[0];

  int& ref = v[0];

  noref = 88;
  ref = 88;

  return 0;
}
