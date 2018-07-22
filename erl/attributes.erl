%%---- Pre-defined attributes
% @doc: Module name should be same as the erlang file name. Otherwise code-loading
% will not work.
-module(attributes).
-compile(export_all).
-author( 'prataprc@gmail.com' ).
-export([main/0]).
-import(lists).
% if left un-specified, version value will be computed using MD5 checksum
%-vsn("1.1").

%%---- Behaviour attributes (interpreted by OTP)
% refer genserver.erl, genfsm.erl, genevent.erl, supervisor.erl

%%---- Pre-processor attributes
% refer records.erl

main() ->
    Info = ?MODULE:module_info(),
    io:format( "~p ~n", [Info] ).
