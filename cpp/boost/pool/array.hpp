
#include <cstddef>
#include <stdexcept>
#include <cassert.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/integer/static_log2.hpp>

// Handles broken standard libraries better than <iterator>
#include <boost/detail/iterator.hpp>
#include <algorithm>

using std::vector;


    template<class T, std::size_t N, std::size_t M>
    class MiVec {
      public:
        T * _data[M];
        vector<T*> _extraData;
        int _lastIndex;
        int _lastData;
        typedef boost::singleton_pool<Mivec, N*sizeof(T)> _pool; 


      public:
        // type definitions
        typedef T              value_type;
        typedef T*             iterator;
        typedef const T*       const_iterator;
        typedef T&             reference;
        typedef const T&       const_reference;
        typedef std::size_t    size_type;
        typedef std::ptrdiff_t difference_type;
    
        // iterator support
        iterator begin() { return elems; }
        const_iterator begin() const { return elems; }
        iterator end() { return elems+N; }
        const_iterator end() const { return elems+N; }

        // reverse iterator support
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_MSVC_STD_ITERATOR) && !defined(BOOST_NO_STD_ITERATOR_TRAITS)
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
#elif defined(_MSC_VER) && (_MSC_VER == 1300) && defined(BOOST_DINKUMWARE_STDLIB) && (BOOST_DINKUMWARE_STDLIB == 310)
        // workaround for broken reverse_iterator in VC7
        typedef std::reverse_iterator<std::_Ptrit<value_type, difference_type, iterator,
                                      reference, iterator, reference> > reverse_iterator;
        typedef std::reverse_iterator<std::_Ptrit<value_type, difference_type, const_iterator,
                                      const_reference, iterator, reference> > const_reverse_iterator;
#else
        // workaround for broken reverse_iterator implementations
        typedef std::reverse_iterator<iterator,T> reverse_iterator;
        typedef std::reverse_iterator<const_iterator,T> const_reverse_iterator;
#endif

        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }
        reverse_iterator rend() { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const {
            return const_reverse_iterator(begin());
        }

        // operator[]
        reference operator[](size_type i) 
        { 
            BOOST_ASSERT( i < N && "out of range" ); 
            return elems[i];
        }
        
        const_reference operator[](size_type i) const 
        {     
            BOOST_ASSERT( i < N && "out of range" ); 
            return elems[i]; 
        }

        // at() with range check
        reference at(size_type i) { rangecheck(i); return elems[i]; }
        const_reference at(size_type i) const { rangecheck(i); return elems[i]; }
    
        // front() and back()
        reference front() 
        { 
            return elems[0]; 
        }
        
        const_reference front() const 
        {
            return elems[0];
        }
        
        reference back() 
        { 
            return elems[N-1]; 
        }
        
        const_reference back() const 
        { 
            return elems[N-1]; 
        }

        // size is constant
        static size_type size() { return N; }
        static bool empty() { return false; }
        static size_type max_size() { return N; }
        enum { static_size = N };

        // swap (note: linear complexity)
        void swap (array<T,N>& y) {
            std::swap_ranges(begin(),end(),y.begin());
        }

        // direct access to data (read-only)
        const T* data() const { return elems; }

        // use array as C array (direct read/write access to data)
        T* c_array() { return elems; }

        // assignment with type conversion
        template <typename T2>
        array<T,N>& operator= (const array<T2,N>& rhs) {
            std::copy(rhs.begin(),rhs.end(), begin());
            return *this;
        }

        // assign one value to all elements
        void assign (const T& value)
        {
            std::fill_n(begin(),size(),value);
        }

        // check range (may be private because it is static)
        static void rangecheck (size_type i) {
            if (i >= size()) { 
                throw std::range_error("array<>: index out of range");
            }
        }

    };

    // comparisons
    template<class T, std::size_t N>
    bool operator== (const array<T,N>& x, const array<T,N>& y) {
        return std::equal(x.begin(), x.end(), y.begin());
    }
    template<class T, std::size_t N>
    bool operator< (const array<T,N>& x, const array<T,N>& y) {
        return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
    }
    template<class T, std::size_t N>
    bool operator!= (const array<T,N>& x, const array<T,N>& y) {
        return !(x==y);
    }
    template<class T, std::size_t N>
    bool operator> (const array<T,N>& x, const array<T,N>& y) {
        return y<x;
    }
    template<class T, std::size_t N>
    bool operator<= (const array<T,N>& x, const array<T,N>& y) {
        return !(y<x);
    }
    template<class T, std::size_t N>
    bool operator>= (const array<T,N>& x, const array<T,N>& y) {
        return !(x<y);
    }

    // global swap()
    template<class T, std::size_t N>
    inline void swap (array<T,N>& x, array<T,N>& y) {
        x.swap(y);
    }


#endif /*BOOST_ARRAY_HPP*/
