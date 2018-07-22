-module(uni).
-export([run/0]).
-define( PREFIX, "<html><meta charset=\"utf-8\"></meta><body><table>" ).
-define( SUFFIX, "</table></body></html>" ).

uniseq(X, Y) -> [ {erlang:list_to_binary(erlang:integer_to_list(I)), I} || I <- lists:seq(X,Y) ].

run() ->
    {ok, Fd} = file:open( "unicode.html", [write,binary] ),
    file:write(Fd, ?PREFIX),
    Txt = [ <<"<tr><td>",D/binary,"</td><td>",X/utf8,"</td>">> || {D,X} <- uniseq(1,10000) ],
    file:write(Fd, Txt),
    file:write(Fd, ?SUFFIX),
    file:close(Fd).
