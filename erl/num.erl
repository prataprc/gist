-module(num).
-export([ factorial/1, qsort/1, qsort3/1,
          primes/1, xfactors/1, primefactors/1, 
          int2str/1, is_palindrome/1, timeit/3 ]).
-export([start/0]).
-import(io_lib).
-import(math).
-import(lists).
-import(lists, [partition/2]).

%% timeit
timediff( {_, X2, Y2}, {_, X1, Y1} ) -> (X2*1000000+Y2) - (X1*1000000+Y1).
timeit( Mod, Func, Args ) ->
    A = now(), apply(Mod, Func, Args), B = now(), timediff(B,A).

%% Factorial - Optimised for tail recursion
factorial(1, Res) -> Res;
factorial(N, Res) -> factorial( N-1, Res*N ).

factorial(0) -> 1;
factorial(1) -> 1;
factorial(N) -> factorial( N-1, N ). %% API

%% Qsort
qsort( Pivot, { Less, Great } ) -> qsort(Less) ++ [Pivot] ++ qsort(Great).
qsort( [] ) -> [];
qsort( [ Pivot | T ]  ) -> qsort( Pivot, partition( fun( Item ) -> Pivot > Item end, T )).

%% Qsort - 20% faster than the previous one.
%%  Possible reasons - Only one list concatination & no lists:reverse().
qsort3([])      -> [];
qsort3([H | T]) -> qsort3_acc([H | T], []).
qsort3_acc([], Acc) -> Acc;
qsort3_acc([H | T], Acc) -> part_acc(H, T, {[], [H], []}, Acc).
part_acc(_, [], {L, E, G}, Acc) -> qsort3_acc(L, (E ++ qsort3_acc(G, Acc)));
part_acc(X, [H | T], {L, E, G}, Acc) ->
        if
            H < X ->
                part_acc(X, T, {[H | L], E, G}, Acc);
            H > X ->
                part_acc(X, T, {L, E, [H | G]}, Acc);
            true -> part_acc(X, T, {L, [H | E], G}, Acc)
        end.

%% conversions
int2str( N ) -> case io_lib:format("~p", [N]) of [S] -> S end.

%% is_palindrome
is_palindrome( N ) -> int2str(N) =:= lists:reverse(int2str(N)).

%% primes
primes( _, [], Res ) -> Res;
primes( N, [H|T], Res ) -> primes( N, T -- lists:seq(H, N, H), [H|Res] ).
primes( 1 ) -> [];
primes( 2 ) -> [2];
primes( N ) -> primes( N, lists:seq(2,N), [] ).

%% Smallest and Largest Factor
divide( N, [] ) -> { 1, N };
divide( N, [Ds|_] ) when N rem Ds =:= 0 -> { Ds, N div Ds };
divide( N, [_|T] ) -> divide( N, T ).
xfactors( N ) -> divide( N, primes(trunc(math:sqrt(N))) ).

%% primefactors
primefactors( N, Res ) ->
    case xfactors( N ) of 
        {S,G} when S =:= 1 -> [G|Res];
        {S,G} -> [ S | primefactors( G, Res ) ]
    end.
primefactors( N ) -> primefactors( N, [] ).

%% start() -> qsort( lists:seq(15000,1,-1) ).
somefunc() -> true.
start() -> 10.
