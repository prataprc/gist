-module(conc).
-compile(export_all).

cpubound(Count, N, St) when Count >= N*N*N*N -> 
    io:format( "CPU Time taken for ~w counts is ~w ~n",
               [N*N*N*N, timer:now_diff(now(), St)] );
cpubound(Count, N, St) ->
    cpubound(Count+1, N, St).

iobound(N, N, St) ->
    io:format( "IO Time taken for ~w counts is ~w ~n",
               [N, timer:now_diff(now(), St)] );
iobound(Count, N, St) ->
    cpubound(1, 15+Count, now()),
    timer:sleep(10),
    iobound(Count+1, N, St).

sudoku(S, E) ->
    Table = sudoku_slv:solve( S, sudoku_gen:generate(switching, S, E)),
    io:format("~w ~n", [Table]). 

par(cpu, N) ->
    spawn( ?MODULE, cpubound, [1, N, now()] );
par(io, N) ->
    spawn( ?MODULE, iobound, [1, N, now()] ).

par(sdk, Size, Elimit ) ->
    knutl:gm(),
    spawn( ?MODULE, sudoku, [Size, Elimit] ).

