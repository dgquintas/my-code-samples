-module(mylists).
-export([sum/1, map/2, filter/2, for/3]).

sum([X]) -> X;
sum([H|T]) -> H + sum(T).

map(F, [X]) -> F(X);
map(F, [H|T]) -> [F(H) | map(F,T) ].

filter(P, [H|T]) ->
  case P(H) of
    true -> [H|filter(P, T)];
    false -> filter(P, T)
  end;
filter(_P, [] ) -> [].

for(_F, N, N) -> [];
for(F, I, N) -> [ F(I) | for(F, I+1, N) ].
