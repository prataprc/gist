#! /usr/bin/env escript

-module(genserv).
-export([ main/1 ]).

main( _Args ) ->
    process_flag( trap_exit, true ),
    {ok, Pid} = gen_server:start_link( {local, genserver}, genserver, [], [] ),
    timer:sleep(200),
    erlang:display({self(), Pid}),
    %genserver:exitwithreason(),
    %genserver:error(),
    %genserver:throw(),
    %erlang:exit(Pid, shutdown),
    genserver:withtimeout(),
    ok.

