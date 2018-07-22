#! /usr/bin/env escript

-module(trycatch).

exprs( exitR ) -> erlang:exit( exitReason );
exprs( exitRA ) -> erlang:exit( exitReasonArgs, [10,20] );
exprs( throw_ ) -> erlang:throw( throwReason );
exprs( error_ ) -> erlang:error( errorReason ).

doexcp( [] ) -> ok;
doexcp( [X | Xs] ) ->
    try exprs( X )
    catch 
        exit:E ->
            io:format("exit ~w~n", [E] ),
            doexcp( Xs );
        error:E ->
            io:format("error ~w~n", [E] ),
            doexcp( Xs );
        E -> %% Default is throw class.
            io:format("Catchall ~w~n", [E] ),
            doexcp( Xs )
    end.

main(_Args) -> doexcp([ exitR, exitRA, throw_, error_ ]).
