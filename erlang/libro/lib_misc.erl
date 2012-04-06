-module(lib_misc).
-export([for/3, 
         qsort/1, 
         pythag/1, 
         perms/1, 
         odds_and_evens_acc/1, 
         on_exit/2,
         keep_alive/2,
         keep_alive_safe/2
     ]
 ).

for(Max, Max, F) -> [F(Max)];
for(I, Max, F) -> [F(I)|for(I+1, Max, F)].

qsort([]) -> [];
qsort([H | T]) -> qsort([ X || X <- T, X < H ])
                  ++ [H] ++
                  qsort([ X || X <- T, X >= H ]).

pythag(N) -> 
  [ {A,B,C} || A <- lists:seq(1,N-1),
               B <- lists:seq(1,N-1),
               C <- lists:seq(1,N-1),
               A*A + B*B =:= C*C,
               A+B+C =< N ].

perms([]) -> [[]];
perms(L) -> [ [H|T] || H <- L, T <- perms(L--[H]) ].


%accumulator example
odds_and_evens_acc(L) -> odds_and_evens_acc(L, [], []).

odds_and_evens_acc([H|T], Odds, Evens) ->
  case H rem 2 of
    0 -> odds_and_evens_acc(T, [H|Odds], Evens);
    1 -> odds_and_evens_acc(T, Odds, [H|Evens])
  end;
odds_and_evens_acc([], Odds, Evens) ->
  {lists:reverse(Odds), lists:reverse(Evens)}.


on_exit(Pid, Fun) ->
    spawn( fun() ->
                process_flag(trap_exit, true),
                link(Pid),
                receive
                    {'EXIT', Pid, Why} ->
                        Fun(Why)
                end
        end).

keep_alive(Name, Fun) ->
    register(Name, Pid = spawn(Fun)),
    on_exit(Pid, fun(_Why) -> keep_alive(Name, Fun) end).

keep_alive_safe(Name, Fun) ->
    Fun2 = fun() -> 
            register(Name, self()),
            on_exit(self(), fun(_Why) -> keep_alive(Name, Fun) end),
            Fun()
    end,
    spawn(Fun2).





  
  
