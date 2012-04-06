-module(frequency).

-export([start/0]). %server 
-export([stop/0, allocate/0, deallocate/1]). %client
-export([init/0]). % needed by spawn

%server shit
start() ->
  register(frequency, spawn(frequency, init, [])).

init() ->
  Frequencies = {get_frequencies(), []},
  loop(Frequencies).

get_frequencies() -> [10, 11, 12, 13, 14, 15].

loop(Frequencies) ->
  receive
    {request, Pid, stop} ->
      case Frequencies of
        {_Free, []} -> 
          reply(Pid, ok);
        {_Free, _Allocd} -> 
          reply(Pid, {error, still_some_allocated_freqs}),
          loop(Frequencies)
      end;
    {request, Pid, allocate} ->
      io:format("About to allocate for ~w~n", [Pid]),
      {NewFrequencies, Reply} = allocate(Frequencies, Pid),
      reply(Pid, Reply),
      loop(NewFrequencies);
    {request, Pid, {deallocate, Freq}} ->
      io:format("About to deallocate ~w for PID ~w~n", [Freq, Pid]),
      {Reply, NewFrequencies} = deallocate(Frequencies, Freq, Pid),
      reply(Pid, Reply),
      loop(NewFrequencies)
  end.

%%%%%%%%%%%%%%%%%%%%%%%%%%

allocate({[], Allocated}, _Pid) ->
  { 
    {[], Allocated},  %freq allocs arent modifd, obviously
    {error, no_frequency}
  };
allocate( Frequencies, Pid) ->
  {[Freq|Free], Allocated} = Frequencies,
  case checkForCount(Allocated, Pid) >= 3 of
    true -> 
      {
        Frequencies,
        {error, too_many_allocations}
      };
    false ->
      { 
        {Free, [{Freq, Pid}|Allocated]}, 
        {ok, Freq}
      }
  end.

deallocate(Frequencies, Freq, Pid) ->
  {Free, Allocated} = Frequencies,
  case lists:keyfind(Freq, 1, Allocated) of
    {Freq, Pid} -> 
      NewAllocated = lists:keydelete(Freq, 1, Allocated),
      {ok, {[Freq, Free], NewAllocated}};
    {Freq, _OtherPid} ->
      {{error, invalid_pid}, Frequencies};
    false ->
      {{error, unallocated_freq}, Frequencies}
  end.

      
reply(Pid, Reply) ->
  io:format("Replying ~w to ~w~n", [Reply, Pid]),
  Pid ! {reply, Reply}.

checkForCount(Allocated, Pid) ->
  count( 
    fun(K) -> 
      case K of
        {_Freq, Pid} -> true;
        {_Freq, _OtherPid} -> false
      end
    end, 
    Allocated
  ).
count(_Pred, []) ->
  0;
count(Pred, [H|T]) ->
  case Pred(H) of
    true -> 1 + count(Pred, T);
    false -> count(Pred, T)
  end.


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%client shit
stop() -> call(stop).
allocate() -> call(allocate).
deallocate(Freq) -> call({deallocate, Freq}).

call(Msg) ->
  frequency ! {request, self(), Msg},
  receive
    {reply, Reply} -> Reply
  end.



