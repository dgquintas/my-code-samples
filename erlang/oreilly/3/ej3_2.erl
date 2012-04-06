-module(ej3_2).
-export([create/1, reverse_create/1]).

create(N) -> lists:reverse(reverse_create(N)).

reverse_create(0) -> [];
reverse_create(N) -> [N |  reverse_create(N-1) ].

