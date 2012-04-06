-module(tut6).
-export([list_max/1]).


list_max([Head | Rest]) ->
  list_max(Rest, Head).

list_max([], Max) ->
  Max;

list_max([Head | Rest], Max_so_far) when Head > Max_so_far ->
  list_max(Rest, Head);

list_max([Head | Rest], Max_so_far) -> 
  list_max(Rest, Max_so_far).



