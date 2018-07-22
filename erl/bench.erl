-module(bench).
-export([ logparser/0, spawnmeasure/1, parse/3 ]).
%-compile(export_all).
-define(LOGFILE, "access.log").
-define(PROCS, 4).

%% Concurrent logic
parseline( <<>>, <<>>, <<>>, <<>>, <<>>, _Tok ) ->
    eol;
parseline( <<" ",Line/binary>>, <<>>, <<>>, <<>>, <<>>, Tok ) ->
    parseline( Line, Tok, <<>>, <<>>, <<>>, <<>> );
parseline( <<" ",Line/binary>>, Host, <<>>, <<>>, <<>>, Tok ) ->
    parseline( Line, Host, Tok, <<>>, <<>>, <<>> );
parseline( <<" ",Line/binary>>, Host, Log, <<>>, <<>>, Tok ) ->
    parseline( Line, Host, Log, Tok, <<>>, <<>> );
parseline( <<"[",D:16,"/",M:24,"/",Y:32,_/binary>>, Host, _, _, <<>>, <<>> ) ->
    { Host, <<D:16,M:24,Y:32>> };
parseline( <<C:8,Line/binary>>, Host, Log, Auth, Date, Tok ) ->
    parseline( Line, Host, Log, Auth, Date, <<Tok/binary,C:8>> ).

parseblock( _Tid, <<>>, _Line ) ->
    true;
parseblock( Tid, <<"\n",Block/binary>>, Line ) ->
    case parseline( Line, <<>>, <<>>, <<>>, <<>>, <<>> ) of
        eol -> true;
        {Host, Date} -> ets:insert( Tid, {Date, Host} )
    end,
    parseblock( Tid, Block, <<>> );
parseblock( Tid, <<C:8,Block/binary>>, Line ) ->
    parseblock( Tid, Block, <<Line/binary,C:8>> ).

parse( Pid, Tid, Block ) ->
    parseblock( Tid, Block, <<>> ),
    Pid ! done.

%% Spawner
recv( Dones, NumBlocks ) when length(Dones) =:= NumBlocks ->
    true;
recv( Dones, NumBlocks ) ->
    receive
        done -> recv( [done | Dones], NumBlocks )
    end.

concparse( _Tid, [], NumBlocks ) ->
    recv( [], NumBlocks );
concparse( Tid, [Block | Blocks], NumBlocks ) ->
    spawn( bench, parse, [ self(), Tid, Block ] ),
    concparse( Tid, Blocks, NumBlocks ).

%% Split logs into blocks of text
logblocks(Fd, BlockSize, Blocks) ->
    case file:pread(Fd, {cur, 0}, BlockSize) of
        {ok, Data} ->
            Trail = case file:read_line(Fd) of {ok, X} -> X; eof -> <<>> end,
            logblocks( Fd, BlockSize, [<<Data/binary,Trail/binary>> | Blocks] );
        eof -> Blocks
    end.

%% Compute the result
result( _, [], _, Res ) -> Res;
result( Tid, [{Date, _Host}| Objects], Date, Res ) ->
    result(Tid, Objects, Date, Res);
result( Tid, [{Date, _Host}| Objects], _PrevDate, Res ) ->
    result( Tid, Objects, Date, [{Date, length(ets:lookup(Tid, Date))} | Res] ).
logparser() ->
    {ok, Fd} = file:open( ?LOGFILE, [binary] ),
    {ok, Info} = file:read_file_info( ?LOGFILE ),
    BlockSize = element( 2, Info ) div ?PROCS,
    Blocks = logblocks( Fd, BlockSize, [] ),
    Tid = ets:new( statphase1, [bag, public] ),
    concparse( Tid, Blocks, length(Blocks) ),
    Res = result( Tid, ets:tab2list(Tid), false, [] ),
    ets:delete( Tid ),
    Res.


%% Measure time taken to spawn process
spawnmeasure( N ) ->
    Max = erlang:system_info( process_limit ),
    io:format("MAximum allowed process : ~p ~n", [Max] ),
    statistics(runtime),
    statistics(wall_clock),
    L = for(1, N, fun() -> spawn( fun() -> wait() end ) end ),
    {_, Time1} = statistics(runtime),
    {_, Time2} = statistics(wall_clock),
    lists:foreach( fun(Pid) -> Pid ! die end, L ),
    U1 = Time1 * 1000 / N,
    U2 = Time2 * 1000 / N,
    io:format("Process spawn time=~p (~p) uS ~n", [U1, U2] ).
wait() -> receive die -> void end.
for(N, N, F) -> [ F() ];
for(I, N, F) -> [ F() | for(I+1, N, F) ].
