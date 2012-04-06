#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

// Declare a custom bidirectional iterator
template<class T>
class custom_iterator 
{
	T *m_Ptr;							// pointer to container value type

public:
	typedef random_access_iterator_tag	iterator_category;
	typedef T	                          value_type;
	typedef value_type&				          reference;
	typedef value_type	*				        pointer;
	typedef int							            difference_type;

	custom_iterator()
	{	// default constructor
	}

	custom_iterator(T *l_Ptr)
	{	// copy constructor
		m_Ptr = l_Ptr;
	}
	custom_iterator(const custom_iterator& rhs)
	{	// copy constructor
    m_Ptr = rhs.m_Ptr;
	}


	reference operator*() const
	{	// return designated object
		return (*m_Ptr);
	}
	reference operator*() 
	{	// return designated object
		return (*m_Ptr);
	}

	custom_iterator& operator++()
	{	// preincrement
		++m_Ptr;
		return (*this);
	}

	custom_iterator& operator--()
	{	// predecrement
		--m_Ptr;
		return (*this);
	}

  custom_iterator& operator+=(difference_type n)
  {
    m_Ptr += n;
    return *this;
  }

  custom_iterator& operator-=(difference_type n)
  {
    m_Ptr -= n;
    return *this;
  }

  value_type& operator[](difference_type n) const
  {
    return *(*this + n);
  }

  value_type& operator[](difference_type n)
  {
    return *(*this + n);
  }

  custom_iterator operator+(difference_type n)  const
  {
    custom_iterator tmp(*this); 
    return tmp += n;
  }

  custom_iterator operator-(difference_type n) const
  {
    custom_iterator tmp(*this); 
    return tmp -= n;
  }

  difference_type operator-(custom_iterator rhs)  const
  {
    return m_Ptr - rhs.m_Ptr;
  }


	custom_iterator operator++(int)
	{	// postincrement
		custom_iterator _Tmp = *this;
		++*this;
		return (_Tmp);
	}

	custom_iterator operator--(int)
	{	// postdecrement
		custom_iterator _Tmp = *this;
		--*this;
		return (_Tmp);
	}



	bool operator==(const custom_iterator &_Right) const
	{	// test for iterator equality
		return (m_Ptr == _Right.m_Ptr);
	}

	bool operator!=(const custom_iterator &_Right) const
	{	// test for iterator inequality
		return (!(m_Ptr == _Right.m_Ptr));
	}
};

// Declare a custom container
template<class T>
class custom
{
public:
	T m_rgArray[16];					// Declare array
	int m_nIndex;						// Index to array

	typedef T							value_type;
	typedef value_type &				reference;
	typedef const value_type &			const_reference;
	typedef custom_iterator<T>		iterator;
	typedef const custom_iterator<T>	const_iterator;
	typedef	int							difference_type;
	typedef int							size_type;

	custom() : m_nIndex(0)				
	{	// init index to 0
	}

	size_type size() const
	{	// return length of sequence
		return m_nIndex;
	}

	size_type max_size() const
	{	// return maximum possible length of sequence
		return 16;
	}

	bool empty() const
	{	// test if sequence is empty
		return (m_nIndex > 0 ? false : true);
	}

	iterator begin()
	{	// return iterator for beginning of mutable sequence
		return custom_iterator<T>(&m_rgArray[0]);
	}

	iterator end()
	{	// return iterator for end of mutable sequence
		return custom_iterator<T>(&m_rgArray[m_nIndex]);
	}

	void push_back(const T &_Val)
	{	// insert element at end
		if (size() < max_size())
			m_rgArray[m_nIndex++] = _Val;
		else
			throw;
	}
};

// functor to print the output of the int
struct print
{
	void operator ()(int x)
	{
		cout << x << endl;
	}
};

// main entry point to program
int  main(void)
{			
	// Declare variables x and y
	vector<int> x;
	custom<int> y;

	// Enter data into containers
	x.push_back(50);
	x.push_back(40);
	x.push_back(60);

	y.push_back(50);
	y.push_back(40);
	y.push_back(60);

	// for loop through containers
	cout << "iterator for loop through vector<int>" << endl;
	for(vector<int>::iterator i = x.begin(); i != x.end(); i++)
		cout << *i << endl;
	cout << endl;

	cout << "iterator for loop through custom<int>" << endl;
	for(custom<int>::iterator j = y.begin(); j != y.end(); j+=1)
		cout << *j << endl;
	cout << endl;

	// for_each loop through containers
	cout << "for_each loop through vector<int>" << endl;
	for_each(x.begin(), x.end(), print());
	cout << endl;

	cout << "for_each loop through custom<int>" << endl;
	for_each(y.begin(), y.end(), print());
	cout << endl;

	// use find algorithm on containers
	vector<int>::iterator vResult;
	cout << "find 40 through vector<int>: ";
	vResult = find(x.begin(), x.end(), 40);
	cout << *vResult << endl;
	cout << endl;

	custom<int>::iterator cResult;
	cout << "find 40 through custom<int>: ";
	cResult = find(y.begin(), y.end(), 40);
	cout << *cResult << endl;
	cout << endl;

	// use max_element algorithm on containers
	cout << "max_element through vector<int>: ";
	vResult = max_element(x.begin(), x.end());
	cout << *vResult << endl;
	cout << endl;

	cout << "max_element through custom<int>: ";
	cResult = max_element(y.begin(), y.end());
	cout << *cResult << endl;
	cout << endl;

	// print out a few results of member functions
	cout << "vector<int>.size: " << int(x.size()) << endl;
	cout << "vector<int>.max_size: " << int(x.max_size()) << endl;
	cout << "vector<int>.empty: " << x.empty() << endl;
	cout << endl;

	cout << "custom<int>.size: " << y.size() << endl;
	cout << "custom<int>.max_size: " << y.max_size() << endl;
	cout << "custom<int>.empty: " << y.empty() << endl;
	cout << endl;

  cout << *(y.begin() + 1) << endl;
  cout << ++(y.begin()[1]) << endl;
  cout << ++(*(y.begin()+1)) << endl;
  cout << *(y.begin() + 1) << endl;

  return 0;
}
