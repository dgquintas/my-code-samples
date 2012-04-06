
inline int f(int x) __attribute__ ((always_inline));

int f(int x)  {
  if( x > 0 )
    return f(x-1);
  else
    return 0;
}

int main(){
  int x = 10;

  f(x);

  return 0;
}
