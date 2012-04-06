#include <cstdlib>
template< typename T1, typename T2 >
struct test_cast {
    test_cast(T2 *p2){
        m_p1 = static_cast<T1*>(p2);
        m_p1 = reinterpret_cast<T1*>(p2);
        m_p1 = const_cast<T1*>(p2);
        m_p1 = (T1*)(p2);
    }
    operator T1 *(){
        return m_p1;
    }

    protected:
        T1 *m_p1;
};

int main(){
    test_cast<int, int> tc1(NULL);
    test_cast<int, short> tc2(NULL); // static_cast peta, const_cast peta
    test_cast<int, int const> tc3(NULL); // static_cast peta, reinterpret_cast peta

    return 0;
}
