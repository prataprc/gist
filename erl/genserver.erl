-module(genserver).
-behaviour(gen_server).

%% gen_server behaviour.
-export([ init/1, handle_call/3, handle_cast/2, handle_info/2, terminate/2,
          code_change/3 ]).

-export([ exitwithreason/0, error/0, throw/0, withtimeout/0 ]).

exitwithreason() -> gen_server:call(genserver, exit_with_reason).

error() -> try gen_server:call(genserver, error)
           catch
              throw:_ -> ok
           end.

throw() -> gen_server:call(genserver, throw).

withtimeout() -> 
    try gen_server:call(genserver, withtimeout, 200) 
    catch
        Class:Term -> erlang:display({timeoutcatch, Class, Term})
    end,
    timer:sleep(500).

%%---- Callbacks for gen_server behaviour

init(_Args) ->
    process_flag( trap_exit, true ),
    erlang:display({init, self()}),
    {ok, 1, 100}.


%%-- Calls

handle_call(exit_with_reason, From, State) ->
    erlang:display({call_exit_with_reason, From, State}),
    {stop, exit_with_reason, State+1, State+1};

handle_call(error, From, State) ->
    erlang:display({call_error, From, State}),
    erlang:error( errored );

handle_call(throw, From, State) ->
    erlang:display({call_throw, From, State}),
    erlang:throw( throwed );

handle_call(withtimeout, From, State) ->
    erlang:display({withtimeout, From, State}),
    timer:sleep(500),
    erlang:display(ok),
    {reply, State+1, State+1};

handle_call(Req, From, State) ->
    erlang:display({callreq, Req, From, State}),
    {reply, State+1, State+1}.

handle_cast(Req, State) ->
    erlang:display({cast, Req, State}).

handle_info( Info, State) ->
    erlang:display({info, Info, State}),
    {noreply, State+1}.

terminate(Reason, State) ->
    erlang:display({terminate, Reason, State}).

code_change(_A, _B, _C) ->
    erlang:error("Code change function not implemented.").


