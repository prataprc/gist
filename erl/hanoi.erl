%% The Towers Of Hanoi
%% Erlang
%% Copyright (C) 2002 Amit Singh. All Rights Reserved.
%% http://hanoi.kernelthread.com
%%
%% Last tested under Erlang (BEAM) emulator version 5.0.2.4
%%

-module(hanoi).
-export([hanoi/1]).
-author('Amit Singh').

m(F,T) -> io:format("~w~s~w~n", [F, " --> ", T]).

h(1,F,U,T) -> m(F, T);
h(N,F,U,T) when N > 0 ->
    h(N - 1, F, T, U),
    m(F, T),
    h(N - 1, U, F, T).

hanoi(0) -> io:format("number of disks cannot be 0~n");
hanoi(N) when N < 0 -> io:format("number of disks must be > 0~n");
hanoi(N) when N > 10 -> io:format("number of disks must be < 10~n");
hanoi(N) -> h(N, 1, 2, 3).
