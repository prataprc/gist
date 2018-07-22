%% #!/usr/bin/env escript

-module(toh).
-export([ main/1, hanoi/1, hanois/2]).

m( {[H|F], U, T} ) -> {F, U, [H|T]}.
a({F, T, U}) -> {F, U, T}.
b({F, U, T}) -> {U, F, T}.
c({U, F, T}) -> {F, U, T}.
h( 1, {F, U, T} ) -> m( {F, U, T} );
h( N, {F, U, T} ) -> c( h( N-1, b( m( a( h( N-1, {F, T, U} )))))).

hanoi(N) -> h( N, { lists:seq(1, N), [], [] } ). 

hanois(Max, Max) -> doneall;
hanois(N,   Max) ->
    {Us, _} = timer:tc(?MODULE, hanoi, [N]),
    io:format( "For ~w discs ~w uS ~n", [ N, Us ] ),
    hanois(N+1, Max).

%% -- Entry point
main( _ ) -> hanois(10, 30).
