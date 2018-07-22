-module(fibonacci).
-export([ fibonacci/1, fibiterator/0 ]).
-import(io_lib).
-import(math).
-import(lists).
-import(lists, [partition/2]).

%% Follow links,
%%      http://en.wikipedia.org/wiki/Fibonacci_number

fibonacci( Result, _, Till, Till )  ->
    Result;
%% Positive fibonacci
%  Fn = Fn-1 + Fn-2
fibonacci( Minus1, Minus2, Count, Till ) when Till > 0 ->
    fibonacci( Minus1+Minus2, Minus1, Count+1, Till );
%% Negative Fibonacci
%  Fn-2 = Fn - Fn-1
fibonacci( Plus1, Plus2, Count, Till ) when Till < 0 ->
    fibonacci( Plus2-Plus1, Plus1, Count-1, Till ).

fibonacci(0) -> 0;                                      % API
fibonacci(1) -> 1;                                      % API
fibonacci(N) when N > 1 -> fibonacci( 1, 0, 1, N );     % API
fibonacci(N) when N < 0 -> fibonacci( 1, 0, -1, N).     % API

fibiterator() -> fun ( {X, Y} ) -> { Y, X+Y } end.

% TODO
