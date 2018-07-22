-module(trapexit).
-export([ main/1, exprs/2 ]).

exprs( PPid, exitR ) -> PPid ! erlang:exit( exitReason );
exprs( PPid, exitRA ) -> PPid ! erlang:exit( exitReasonArgs, [10,20] );
exprs( PPid, throw_ ) -> PPid ! erlang:throw( throwReason );
exprs( PPid, error_ ) -> PPid ! erlang:error( errorReason ).

spawns( [] ) -> ok;
spawns( [E | Es] ) ->
    spawn_link( ?MODULE, exprs, [self(), E] ),
    spawns(Es).

flush() ->
    receive
        X -> io:format( ">>> ~w ~n", [X] ), flush()
    after 0 -> ok
    end.

recv() ->
    receive
        X ->
            io:format("*** ~w ~n", [X] ),
            recv()
    after 1000 ->
        ok
    end.

main( _Args ) ->
    flush(),
    process_flag( trap_exit, true ),
    spawns([ exitR, exitRA, throw_, error_ ]),
    recv().

