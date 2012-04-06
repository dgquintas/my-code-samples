    %module mymodule
    %include "std_string.i"

    %{
    #include "some_class.h"
    %}

    %include "some_class.h"
