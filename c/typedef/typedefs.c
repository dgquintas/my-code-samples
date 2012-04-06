
typedef enum {
  TYPE_DOUBLE,
  TYPE_INT
} Type;

void f(Type t, void* data){
  switch( t ){
    case TYPE_DOUBLE:
      typedef float foo;
      break;
    case TYPE_INT:
      typedef int foo;
      break
  }

  float d = (foo)data;

}
