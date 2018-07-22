-module(bitsyntax).
-export([simple/1]).

simple(<<X>>) -> X.
