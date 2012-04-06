void foo(int* const x){
  x = (int*)123;
  x[0] = 1;
  x[1] = 2;

}

int main(){
  int x[2];
  foo(x);

  return 0;
}
