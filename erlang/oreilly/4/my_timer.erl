-module(my_timer).
-export([sleep/1]).


sleep(T) ->
  receive
  after 
    T -> true
end.

