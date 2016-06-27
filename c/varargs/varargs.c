#include <stdarg.h>
#include <stdio.h>


void f(int num_args, int a, ...) {
    int i;
    va_list ap;
    va_start(ap, a); /* "ap" becomes the handler, "a" is gets the 1st elem */
    for (i = 0; i < num_args; i++) {
        printf("%d-th arg: %d\n", i, a);
        a = va_arg(ap, int); /* refresh "a", get next from ap */
    }
    va_end(ap); /* destroy "ap" */
}


int main() {
    f(3, 14, 88, 69);
    return 0;
}
