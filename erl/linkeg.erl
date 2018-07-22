-module(linkeg).

-compile([ export_all ]).

start_proc() ->
    spawn_link( ?MODULE
