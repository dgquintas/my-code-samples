-module(safe_spawn).
-compile(export_all).

%% Write a function start(AnAtom, Fun) to register AnAtom as spawn(Fun).
%% Make sure your program works correctly in the case when two
%% parallel processes simultaneously evaluate start/2. In this case,
%% you must guarantee that one of these processes succeeds and the
%% other fails.

start(AnAtom, Fun) ->
  Requester = self(), 

  %% the trick is to rely on the atomicity of spawn, and try
  %% to register while already inside the spawn, by means
  %% of the self() function to retrieve one own's Pid.
  %% The result of the call to register/2 is communicated back
  %% to Requester by means of message passing. 
  Fun2 = fun() -> 
      case catch register(AnAtom, self()) of
        true -> 
          Requester ! {ok, self()},
          Fun();
        _ -> Requester ! {failed, self(), AnAtom}
      end
  end,
  Pid = spawn(Fun2), %% this Pid == self() inside Fun2

  receive
    {ok, Pid} ->
      {ok, Pid};
    {failed, Pid, AnAtom} ->
      {failed, AnAtom}
  end.

