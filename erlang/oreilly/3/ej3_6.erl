-module(ej3_6).
-export([quicksort/1, mergesort/1]).

% Quicksort 
% The head of the list is taken as the pivot; the list is then split
% according to those elements smaller than the pivot and the rest. These two
% lists are then recursively sorted by quicksort, and joined together, with the
% pivot between them.  


quicksort([H | T]) ->
  % algo menor que H ++ H ++ algo mayor o igual que H
  {Left, Right} = lists:partition(fun(X) -> X < H end, T),
  quicksort(Left) ++ [H] ++ quicksort(Right);
quicksort([]) -> [].

% Merge sort 
% The list is split into two lists of (almost)
% equal length. These are then sorted separately and their results merged in
% order

mergesort(L) ->
  

split(L) ->


merge([], R) -> R;
merge(L, []) -> L;

merge(L, R) ->
  [LHead | LRest ] = L,
  [RHead | RRest ] = R,
  if
    LHead > RHead -> [RHead | merge(L, RRest)]  ;
    true -> [LHead | merge(LRest, R)]
  end.




