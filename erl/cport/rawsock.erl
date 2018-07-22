-module(rawsock).
-include("ethframe.hrl").
-export([ start_link/0, start/0, stop/0, restart/1 ]).
-export([ init/1, handle_call/3, handle_cast/2, handle_info/2, terminate/2,
           code_change/3 ]).
-behaviour(gen_server).

% Supress unused warnings
-export([ rxproc/0, rxport/1, txproc/0, txport/1 ]).

-define(SERVERNAME, rawsock).
-define(START_ARGS, [ {local, ?SERVERNAME}, ?MODULE, [], [] ]).
-define(TX_TIMEOUT, 10000).
-define(HOSTMAC, <<16#00,16#1c,16#c0,16#f3,16#17,16#05>>).
-define(DESTMAC, <<16#68,16#7f,16#74,16#e5,16#88,16#8e>>).

%%---- API
start_link() -> apply( gen_server, start_link, ?START_ARGS ).
start() -> apply( gen_server, start, ?START_ARGS ).
stop() -> gen_server:cast( ?SERVERNAME, stop ).
restart( What ) -> gen_server:cast( ?SERVERNAME, {restart, What} ).

%testsend() ->
%    Payload = lists:foldl( fun(_, Acc) -> <<0,Acc/binary>> end, <<0>>,
%                           lists:seq(1,1500) ),
%    Frame = <<?DESTMAC/binary,?HOSTMAC/binary,0,0,Payload/binary>>,
%    ?PROCNAME_TX ! { rawsock, self(), {Frame, ?DESTMAC} },
%    receive Any -> Any end. 

%%---- Gen-server callbacks

init( _Args ) ->
    process_flag( trap_exit, true ),
    Rx = spawn_monitor( fun ?MODULE:rxproc/0 ),
    Tx = spawn_monitor( fun ?MODULE:txproc/0 ),
    { ok, {Rx, Tx} }.

handle_call( Reason, From, State ) ->
    { reply, {Reason, From}, State }.

handle_cast( stop, State ) ->                       % terminate
    { stop, normal, State };
handle_cast( {restart, What}, State ) ->            % restart ports
    {noreply, restartport( What, State )}.

handle_info( {'DOWN', Monref, process, Pid, normal}, State ) ->
    io:format("Port stopped process : ~w, Monitor : ~w ~n", [ Pid, Monref ]),
    { noreply, State };
handle_info( {'DOWN', _, process, _, {rxport, Reason}}, State ) ->
    io:format("Rx port going down (reason ~w) restart ... ~n", [Reason] ),
    { noreply, restartport( rxport, State ) };
handle_info( {'DOWN', _, process, _, {txport, Reason}}, State ) ->
    io:format("Tx port going down (reason ~w) restart ... ~n", [Reason] ),
    { noreply, restartport( txport, State ) };
handle_info( timeout, State ) ->
    { noreply, State }.

code_change( _OldVsn, State, _Extra ) ->
    {ok, State}.

terminate( normal, {Rx, Tx} ) ->
    {Rxpid, _RxMon} = Rx,
    {Txpid, _TxMon} = Tx,
    Rxpid ! { 'EXIT', self(), stop },
    Rxpid ! Txpid ! stop.

%% Functions
restartport( What, State ) ->
    { {Rxpid, _Rxmon}=Rx, {Txpid, _Txmon}=Tx } = State,
    case What of
        rxport ->
            Rxpid ! stop,
            RxNew = spawn_monitor( fun ?MODULE:rxproc/0 ),
            {RxNew, Tx};
        txport ->
            Txpid ! stop,
            TxNew = spawn_monitor( fun ?MODULE:txproc/0 ),
            {Rx, TxNew}
    end.

%% Rx Port server to receive ethernet frames.
rxproc() ->
    process_flag( trap_exit, true ),
    Port = open_port( {spawn, './sockrx'}, [{packet, 2}, binary, exit_status] ),
    rxport(Port).

rxport(Port) ->
    receive 
        {Port, {data, Data}} ->
            dispatch( binary_to_term(Data) ),
            %rxport(Port);
            closeport(Port),
            exit(normal);
        {'EXIT', Port, Reason} ->
            exit({rxport, Reason});
        stop ->
            closeport(Port),
            exit(normal)
    end.

dispatch({ Framelen, Frame, Hdrlen, Hdr }) ->
    Parts = ethframe:dec( Frame ),
    <<Ts:64, Caplen:32/native, Pcklen:32/native>> = Hdr,
    io:format("Length ~p ~n", [ {Framelen, Hdrlen} ] ), 
    io:format("Header ~p ~n", [ {Ts, Caplen, Pcklen} ] ), 
    {}.

%% Tx Port server to receive ethernet frames.
txproc() ->
    %process_flag( trap_exit, true ),
    %Port = open_port( {spawn, './socktx'}, [{packet, 2}, binary, exit_status] ),
    %txport(Port).
    {}.

txport(Port) ->
    receive 
        {rawsock, Pid, Frame} ->
            erlang:port_command(Port, term_to_binary(Frame)),
            receive {Port, {data, Ok}} -> Pid ! binary_to_term(Ok) end,
            txport(Port);
        {'EXIT', Port, Reason} ->
            exit({txport, Reason});
        stop ->
            closeport(Port),
            exit(normal)
    end.

%%---- Helper functions
closeport( Port ) ->
    Port ! { self(), close },
    receive { Port, closed } -> true end.

bin2hex( Msg, Bin ) ->
    S = lists:concat( [io_lib:format("~.16B",[X]) || <<X:4>> <= Bin ] ),
    io:format(" ~s : ~s ~n", [ Msg, S ] ).
