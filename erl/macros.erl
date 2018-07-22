#! /usr/bin/env escript

-module(macros).

-define(INT(X), is_integer(X)).
-define(INT(X,Y), is_integer(X) andalso is_integer(Y)).
-define(INT(X,Y,Z), is_integer(X) andalso is_integer(Y) andalso is_integer(Z)).

fn(X) when ?INT(X) -> X;
fn(_) -> 0.

fn(X,Y) when ?INT(X,Y) -> X+Y;
fn(_,_) -> 0.

fn(X,Y,Z) when ?INT(X,Y,Z) -> X+Y+Z;
fn(_,_,_) -> 0.

main(_) ->
    erlang:display(fn(10)),
    erlang:display(fn(a)),
    erlang:display(fn(10,20)),
    erlang:display(fn(10,20,30)).
