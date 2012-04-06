#!/usr/bin/env escript

main(_) -> 
    {ok, Context} = erlzmq:context(),
    {ok, Publisher} = erlzmq:socket(Context, pub),
    ok = erlzmq:bind(Publisher, "tcp://*:5556"),

    loop(Publisher),

    %% we never get here
    ok = erlzmq:close(Publisher),
    ok = erlzmq:term(Context).

loop(Publisher) -> 
    Zipcode = random:uniform(1000000),
    Temperature = random:uniform(215) - 80,
    Relhumidity = random:uniform(50) + 10,

    %% send to all subscribers
    Msg = list_to_binary(
        io_lib:format("~5..0b ~b ~b",
            [Zipcode, Temperature, Relhumidity])),
    ok = erlzmq:send(Publisher, Msg),

    loop(Publisher).


