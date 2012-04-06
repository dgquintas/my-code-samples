-module(geometry).
-export([area/1]).

area({rectangle, Width, Height}) -> Width * Height; %ojo al ;
area({square, X}) -> X*X ;
area({circle, R}) -> 3.141592 * R * R. %cuando se define del todo, punto



