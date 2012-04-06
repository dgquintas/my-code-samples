-module(ej3_5).
-export([filter/2, reverse/1, concatenate/1, flatten/1]).

filter([], _N) -> 
  [];
filter([H | T], N) ->
  if 
    H =< N -> [H | filter(T, N)];
    true -> filter(T,N)
  end.
%% equiv:

%% filter([H | T], N) when H =< N -> 
%%   [H | filter(T, N)];
%% filter([_H | T], N) ->
%%   filter(T,N).
 
reverse(L) -> 
  reverse(L, []).

reverse([ H | T ], R) ->
  reverse(T, [H | R]);
reverse([], R) ->
  R.


%% concatenate([[1,2,3], [], [4, five]]) ⇒ [1,2,3,4,five].
concatenate([HL | RL]) ->
  HL ++ concatenate(RL);
concatenate([]) ->
  [].

%% flatten([[1,[2,[3],[]]], [[[4]]], [5,6]]) ⇒ [1,2,3,4,5,6].
flatten([H|T]) ->
  case is_list(H) of
    true -> flatten(H) ++ flatten(T);
    false -> [H | flatten(T)]
  end;

flatten([]) -> [].


