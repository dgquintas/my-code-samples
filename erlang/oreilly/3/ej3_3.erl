#!/usr/bin/env escript
-module(ej3_3).
-export([main/1, ints1_to_n/1, evens1_to_n/1]).

ints1_to_n(N) ->
  ints1_to_n(1,N).

ints1_to_n(I, N) when I =< N -> 
  io:format("Number:~p~n", [I]),
  ints1_to_n(I+1, N);
ints1_to_n(_, _N) -> ok.

evens1_to_n(N) ->
  evens1_to_n(2,N).

evens1_to_n(I, N) when I =< N, I rem 2 == 0 -> 
  io:format("Number:~p~n", [I]),
  evens1_to_n(I+2, N);
evens1_to_n(_, _N) -> ok.



main([N | _]) ->
  %% to prove that the "ok" atom isnt printed to stdout
  X = list_to_integer(N),
  ints1_to_n(X),
  io:format("~n"),
  evens1_to_n(X);
main(_N) ->
  io:format("Invoke with at least one (numerical) argument~n").


