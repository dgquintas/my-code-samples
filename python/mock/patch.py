from mock import patch
import my_module

def some_function():
    print( my_module.Foo )
    foo = my_module.Foo("abc",123)
    print( foo.a )
    return foo.return_string()

with patch('my_module.Foo', spec=my_module.Foo, spec_set=True) as mock:
    instance = mock.return_value
    instance.return_string.return_value = 'the result'
    instance.a = 123
    result = some_function()
    assert result == 'the result'
    print(mock.call_args)
