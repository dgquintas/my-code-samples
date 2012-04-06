-module(ring_bench).
-compile(export_all).

start(N,M) ->
  MasterPid = self(),
  %%master's next is the pid of the Nth proc
 
  statistics(runtime),
  statistics(wall_clock),

  MastersNext = create(N-1, MasterPid),

  {_, Time1_1} = statistics(runtime),
  {_, Time2_1} = statistics(wall_clock),
  U1_1 = Time1_1 * 1000 / N,
  U2_1 = Time2_1 * 1000 / N,
  io:format("Creation of ~p processes = ~p (~p) microseconds~n", 
    [N, U1_1, U2_1]),

  MasterPid ! {msg, M,0},
  master(MastersNext), 

  {_, Time1_2} = statistics(runtime),
  {_, Time2_2} = statistics(wall_clock),
  NumOfMsgs = N*M,
  U1_2 = Time1_2,
  U2_2 = Time2_2,
  io:format("Circulation time for ~p messages = ~p (~p) milliseconds~n", 
    [NumOfMsgs, U1_2, U2_2]).


create(1,MasterPid) ->
  %%eventually node 1 will have as next the pid of the master
  spawn(?MODULE, loop, [MasterPid]);
create(N,MasterPid) ->
  %%node N will have as next the PID of node N-1
  spawn(?MODULE, loop, [create(N-1, MasterPid)]).


loop(Next) ->
  receive
    {msg, M, Count} ->
      Next ! {msg, M, Count+1},
      loop(Next)
  end.

master(Next) ->
  receive
    {msg, M, Count} ->
      case M > 0 of
        true -> 
          Next ! {msg, M-1, Count+1},
          master(Next);
        false -> 
          io:format("Circulated ~p messages~n", [Count]),
          done
      end
  end.

    


