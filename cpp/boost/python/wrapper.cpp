#include <boost/python.hpp>
using namespace boost::python;

extern char const* greet();

BOOST_PYTHON_MODULE(hello)
{
    def("greet", greet);
}
