-module(tut3).
-export([convert_length/1]).

convert_length({cm, X}) ->
  {inch, X / 2.54};
convert_length({inch, Y}) ->
  {cm, Y * 2.54}.

