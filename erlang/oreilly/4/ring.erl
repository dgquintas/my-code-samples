-module(ring).
-export([start/3, stop/0]).
-export([init/1]).

start(M, N, Msg) ->
  register(ring, spawn(?MODULE, init, [N])),
  circulateMsgs(M, Msg).
  
stop() ->
  ring ! stop.

init(1) ->
  Next = whereis(ring),
  io:format("Last proc ~w has ~w as next~n",[self(), Next]),
  loop(Next);
init(N) ->
  Next = spawn(?MODULE, init, [N-1]),
  io:format("Spawned proc ~w has just spawned next as ~w~n",[self(), Next]),
  loop(Next).


loop(Next) ->
  receive
    stop -> 
      terminate(),
      Next ! stop;
    {msg, Msg} -> 
      io:format("Proc ~w rcvd msg. Fwding it to ~w~n",[self(), Next]),
      timer:sleep(100),
      Next ! {msg,Msg},
      loop(Next)
  end.

terminate() ->
  io:format("Process ~w quitting...~n", [self()]).

circulateMsgs(1, Msg) ->
  ring ! {msg,Msg};
circulateMsgs(N, Msg) ->
  ring ! {msg,Msg},
  circulateMsgs(N-1, Msg).


