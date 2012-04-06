-module(area_server0).
-export([loop/0]).

loop() ->
    receive
        {rectangle, Width, Ht} -> 
            io:format("Area of rectangle is ~p~n", [Width*Ht]),
            loop();
        {circle, R} -> 
            io:format("Area of circle is ~p~n", [2 * 3.141592 * R*R]),
            loop();
        Other ->
            io:format("Faaail: ~p~n", [Other]),
            loop()
    end.




    
