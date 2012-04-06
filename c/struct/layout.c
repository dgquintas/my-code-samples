#include <stdio.h>

typedef struct {
               // 64 / 32
    int a;     // 4  / 4
    // padding of 4  / -
    char* ptr; // 8  / 4
    float f;   // 4  / 4
    // padding of 4  / -
    double d;  // 8  / 4 padding, 8 size   
               // 32 / 20

} Foo;

typedef struct {
    int a;     // 4 / 4
    float f;   // 4 / 4
    // no padding needed
    char* ptr; // 8 / 4
    double d;  // 8 / 4 padding, 8 size
               // 24 / 20 
} Bar;


int main() {
    Foo f;

    size_t sz = sizeof(f.a);
    void* ptr = &f.a;
    int is_multiple = (((long)ptr) % sz) == 0;
    printf("int: 0x%x\t\tMultiple of %d: %d\n", ptr, sz, is_multiple );
    
    sz = sizeof(f.ptr);
    ptr = &f.ptr;
    is_multiple = (((long)ptr) % sz) == 0;
    printf("ptr: 0x%x\t\tMultiple of %d: %d\n", ptr, sz, is_multiple );

    sz = sizeof(f.f);
    ptr = &f.f;
    is_multiple = (((long)ptr) % sz) == 0;
    printf("float: 0x%x\tMultiple of %d: %d\n", ptr, sz, is_multiple );
 
    sz = sizeof(f.d);
    ptr = &f.d;
    is_multiple = (((long)ptr) % sz) == 0;
    printf("double: 0x%x\tMultiple of %d: %d\n", ptr, sz, is_multiple );

    printf("Sizeof(Foo) = %d\n", sizeof(Foo));


    printf("Sizeof(Bar) = %d\n", sizeof(Bar));

    Bar b;
    printf("__alignof__(Bar.d) = %d\n", __alignof__(b.a));
    printf("__alignof__(Bar.d) = %d\n", __alignof__(b.ptr));
    printf("__alignof__(Bar.d) = %d\n", __alignof__(b.f));
    printf("__alignof__(Bar.d) = %d\n", __alignof__(b.d));
    printf("__alignof__(Bar) = %d\n", __alignof__(Bar));



    return 0;
}
