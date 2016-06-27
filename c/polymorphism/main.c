#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

typedef struct Interface_vtable {
  void (*method_a)();
  void (*method_b)();
} Interface_vtable;

typedef struct Interface { const Interface_vtable *vtable; } Interface;

///////////////////////////////////////////////////////
typedef struct Impl {
  Interface base;  // gotta be the first one

  int a;
  float b;
} Impl;

void method_a_impl(Interface *interface) {
  Impl *impl = (Impl *)interface;
  printf("A value: %d\n", impl->a);
}

void method_b_impl(Interface *interface) {
  Impl *impl = (Impl *)interface;
  printf("B value: %f\n", impl->b);
}
///////////////////////////////////////////////////////

Impl *Impl_create(int a, float b) {
  static const Interface_vtable interface_vtable = {method_a_impl,
                                                    method_b_impl};
  Impl *impl = malloc(sizeof(Impl));
  memset(impl, 0, sizeof(Impl));
  impl->base.vtable = &interface_vtable;

  impl->a = a;
  impl->b = b;

  return impl;
}

void Impl_destroy(Impl *impl) { free(impl); }

int main() {
  Impl *impl = Impl_create(1, 3.14);

  fprintf(stderr, "*impl       = 0x%p\n", impl);
  fprintf(stderr, "&impl->base = 0x%p\n", &impl->base);
  assert((void *)impl == (void *)&impl->base);

  method_a_impl(&impl->base);
  method_b_impl(&impl->base);

  Impl_destroy(impl);
  return 0;
}
