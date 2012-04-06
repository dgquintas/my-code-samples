    #ifndef _SOME_CLASS_H_
    #define _SOME_CLASS_H_
#include <string>
    class SomeClass
    {
    private:
        int     mValA;
        int     mValB;
    public:
        SomeClass();
        SomeClass(int a, int b);
        virtual ~SomeClass() {};
        void MethodA();
        void MethodB(int a = 5);
        int GetValA();
        std::string bla() const;
    };

    #endif  // _SOME_CLASS_H_

