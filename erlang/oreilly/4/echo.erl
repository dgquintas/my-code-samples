-module(echo).
-export([go/0, loop/0]).

go() ->
  register(echo, spawn(echo, loop, [])),
  echo ! {self(), hello},
  receive
    {_Pid, Msg} -> 
      io:format("~w~n", [Msg])
  end.

loop() ->
  receive
    {From, Msg} ->
      From ! {self(), Msg},
      loop();
    stop -> 
      true
  end.

