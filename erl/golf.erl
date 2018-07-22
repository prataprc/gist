#!/usr/bin/env escript

-module(golf).
-export([ pickholes/1, main/1 ]).

pick( _,           Res,         _,   _, Ts, Ts ) -> Res;
pick( [{I,X} | T], Res, {X, Y, Z}, Rem, Rs, Ts ) -> pick( T, [{I,X} | Res], {0,Y,Z}, Rem, Rs+1, Ts );
pick( [{I,Y} | T], Res, {X, Y, Z}, Rem, Rs, Ts ) -> pick( T, [{I,Y} | Res], {X,0,Z}, Rem, Rs+1, Ts );
pick( [{I,Z} | T], Res, {X, Y, Z}, Rem, Rs, Ts ) -> pick( T, [{I,Z} | Res], {X,Y,0}, Rem, Rs+1, Ts );
pick( L,           Res, {0, 0, 0}, Rem, Rs, Ts ) -> pick( L++Rem, Res, {}, [], Rs, Ts );
pick( [H | T],     Res,        {},  [], Rs, Ts ) -> pick( T, [H | Res], {}, [], Rs+1, Ts );
pick( [H | T],     Res,      Slot, Rem, Rs, Ts ) -> pick( T, Res, Slot, [H|Rem], Rs, Ts ).
    
%% API
pickholes(L) -> pick( shuffle(L), [], {3,4,5}, [], 0, 6 ).

%% -- Entry point
main( _ ) -> 
    random:seed( now() ),
    erlang:display( pickholes( ootygame() ) ).

%% -- Sample data
ootygame() ->
    [{1,  5}, {2,  3}, {3,  4}, {4,  4}, {5,  5}, {6,  4}, {7,  3},
     {8,  4}, {9,  3}, {10, 4}, {11, 3}, {12, 4}, {13, 4}, {14, 3},
     {15, 4}, {16, 5}, {17, 4}, {18, 4}].  

%% Knuth / Fisher - Yates shuffle algorithm
shuffle(List) ->
    randomize(round(math:log(length(List)) + 0.5), List).

randomize(1, List) -> randomize(List);
randomize(T, List) -> 
    lists:foldl( fun(_E, Acc) -> randomize(Acc) end,
                 randomize(List),
                 lists:seq(1, (T - 1))
               ).
randomize(List) ->
    D = lists:map( fun(A) -> {random:uniform(), A} end, List ),
    {_, D1} = lists:unzip(lists:keysort(1, D)), 
    D1.


