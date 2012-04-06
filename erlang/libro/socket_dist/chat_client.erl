-module(chat_client).

-import(io_widget, 
    [get_state/1, insert_str/2, set_prompt/2, set_state/2,
     set_title/2, set_handler/2, update_state/3]).

-export([start/0, test/0, connect/5]).


start() ->
    connect("localhost", 2223, "AsDT67aQ", "general", "foobar").

test() ->
    connect("localhost", 2223, "AsDT67aQ", "general", "joe"),
    connect("localhost", 2223, "AsDT67aQ", "general", "jane"),
    connect("localhost", 2223, "AsDT67aQ", "general", "fulano"),
    connect("localhost", 2223, "AsDT67aQ", "general", "zutano").

connect(Host, Port, HostPsw, Group, Nick) ->
    spawn(fun() -> handler(Host, Port, HostPsw, Group, Nick) end).

handler(Host, Port, HostPsw, Group, Nick) ->
    process_flag(trap_exit, true),
    Widget = io_widget:start(self()),
    set_title(Widget, Nick),
    set_state(Widget, Nick),
    set_prompt(Widget, [Nick, " > "]),
    set_handler(Widget, fun parse_command/1),
    start_connector(Host, Port, HostPsw),
    disconnected(Widget, Group, Nick).

disconnected(Widget, Group, Nick) ->
    receive 
        {connected, MM} -> %% MM = man in the middle
            insert_str(Widget, "connected to server\nsending data\n"),
            MM ! {login, Group, Nick},
            wait_login_response(Widget, MM);

        {Widget, destroyed} ->
            exit(died);

        {status, S} ->
            insert_str(Widget, to_str(S)),
            disconnected(Widget, Group, Nick);

        Other ->
            io:format("chat_client disconnected unexpected:~p~n", [Other]),
            disconnected(Widget, Group, Nick)
    end.

start_connector(Host, Port, Pwd) ->
    S = self(), %% esto es necesario para obtener el PID (futuro)
                %% padre de proc creado por el siguiente spawn.
                %% De ponerlo directamente en la def de la fun, self()
                %% se evaluaria ya dentro del proceso hijo
    spawn_link(fun() -> try_to_connect(S, Host, Port, Pwd) end).

try_to_connect(Parent, Host, Port, Pwd) ->
    %% parent es el pid del proceso padre de este proceso
    case lib_chan:connect(Host, Port, chat, Pwd, []) of
        {error, _Why} ->
            Parent ! {status, {cannot, connect, Host, Port}},
            sleep(2000),
            try_to_connect(Parent, Host, Port, Pwd);
        {ok, MM} ->
            lib_chan_mm:controller(MM, Parent),
            Parent ! {connected, MM},
            exit(connectorFinished)
    end.

wait_login_response(Widget, MM) ->
    receive 
        {MM, ack} ->
            active(Widget, MM);
        Other -> 
            io:format("chat_client login unexpedted:~p~n", [Other]),
            wait_login_response(Widget, MM)
    end.

active(Widget, MM) ->
    receive
        {Widget, Nick, Str} ->
            MM ! {relay, Nick, Str},
            active(Widget, MM);
        {MM, {msg, From, Pid, Str}} ->
            insert_str(Widget, [From, "@", pid_to_list(Pid), " ", Str, "\n"]),
            active(Widget, MM);
        {'EXIT', Widget, windowDestroyed} ->
            MM ! close;
        {close, MM} ->
            exit(serverDied);
        Other ->
            io:format("chat_client active unexpected:~p~n", [Other]),
            active(Widget, MM)
    end.

sleep(T) ->
    receive 
    after T -> true
    end.

to_str(Term) ->
    io_lib:format("~p~n", [Term]).

parse_command(Str) -> skip_to_gt(Str). %ie, skip ta el >

skip_to_gt(">" ++ T ) -> T; %%matching de ">" seguido de T. 
skip_to_gt([_ | T])   -> skip_to_gt(T);
skip_to_gt([])        -> exit("no >").
