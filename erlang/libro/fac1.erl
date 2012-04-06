-module(fac1).
-export([main/1]).

main([A]) ->
    F = fac( list_to_integer(atom_to_list(A)) ),
    io:format("~p~n", [F]),
    init:stop().

fac(0) -> 1;
fac(N) -> N*fac(N-1).
