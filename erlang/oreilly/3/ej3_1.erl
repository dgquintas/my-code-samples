-module(ej3_1).
-export([sum/1, sum/2]).

sum(N) when N > 0 -> 
  N + sum(N-1);
sum(0) -> 0.

sum(N, M) when N < M ->
  N + sum(N+1, M);
sum(M,M) -> 
  M.
