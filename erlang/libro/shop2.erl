-module(shop2).
-export([total/1]).
-import(lists, [map/2, sum/1]). % like from lists import map, sum


total(L) ->
  GetPriceFor = fun({What, N}) -> shop:cost(What) * N end,
  sum( map( GetPriceFor, L ) ).


