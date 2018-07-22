#! /usr/bin/env escript

-module(mutualf).

compoundint(P, N, R) ->
    P * math:pow( (1+R/100), N ).

returns( _, 0, _, Acc ) -> Acc;

returns( EMI, Months, Period, Acc ) ->
    Interest = compoundint(EMI, (Months / Period), 3),
    erlang:display(Interest),
    returns( EMI, Months-1, Period, Acc+Interest ).

returns( EMI, Months, Period ) -> returns( EMI, Months, Period, 0 ).

main(_Args) ->
    io:format( "~w ~n", [returns( 2000, 24, 3 )] ).
