template <typename T>
class Foo {
    public:
        Foo(T x) : x_(x) {}
        void DoStuff();
    private:
        T x_;
};
