#!/usr/bin/env escript

% must be main
main([A]) ->
    F = fac( list_to_integer(A) ),
    io:format("~p~n", [F]).

fac(0) -> 1;
fac(N) -> N*fac(N-1).
