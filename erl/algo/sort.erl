-module(sort).
-compile(export_all).

insert( N, [], Prefix )                -> lists:reverse([N|Prefix]);
insert( N, [H|T], Prefix ) when H >= N -> lists:reverse([H,N|Prefix]) ++ T;
insert( N, [H|T], Prefix ) when H < N  -> insert( N, T, [H|Prefix] ).
insort( [], Sorted )     -> Sorted;
insort( [H|T], Sorted )  -> insort( T, insert( H, Sorted, [] ) ).
insort( [H|T] )  -> insort( T, [H] ).

qsort([]) ->
    [];
qsort([H | T]) -> 
    qsort([ X || X <- T, X < H ]) ++ [H] ++ qsort([ X || X <- T, X >= H ]).


% Profiling
profile() ->
    LSorted = lists:seq(1,1000000),
    LRevers = lists:reverse( lists:seq(1,1000000) ),
    LRandom = [ random:uniform(1000000) || _ <- lists:seq(1,1000000) ],
    io:format( "For pre-sorted list : ~n" ),
    io:format( "  Builtin sort ~wuS ~n",
               [ element(1, timer:tc( lists, sort, [ LSorted ] )) ]),
    %io:format( "  Insert sort ~wuS ~n",
    %           [ element(1, timer:tc( ?MODULE, insort, [ LSorted ] )) ]),
    %io:format( "  Quick sort ~wuS ~n",
    %           [ element(1, timer:tc( ?MODULE, qsort, [ LSorted ] )) ]),
    io:format( "For reverse-sorted list : ~n" ),
    io:format( "  Builtin sort ~wuS ~n",
               [ element(1, timer:tc( lists, sort, [ LRevers ] )) ]),
    %io:format( "  Insert sort ~wuS ~n",
    %           [ element(1, timer:tc( ?MODULE, insort, [ LRevers ] )) ]),
    %io:format( "  Quick sort ~wuS ~n",
    %           [ element(1, timer:tc( ?MODULE, qsort, [ LRevers ] )) ]),
    io:format( "For random list : ~n" ),
    io:format( "  Builtin sort ~wuS ~n",
               [ element(1, timer:tc( lists, sort, [ LRandom ] )) ]).
    %io:format( "  Insert sort ~wuS ~n",
    %           [ element(1, timer:tc( ?MODULE, insort, [ LRandom ] )) ]),
    %io:format( "  Quick sort ~wuS ~n",
    %           [ element(1, timer:tc( ?MODULE, qsort, [ LRandom ] )) ]).
