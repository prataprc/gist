#! /usr/bin/env escript

-module(improper).

match([]) -> ok;
match([X|Xs]) -> erlang:display(X), match(Xs).

main(_Args)->
    match([1,2,3]),
    match([1,2,3|[]]),
    match([1,2,3|[4,5,6]]).
