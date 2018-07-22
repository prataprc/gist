-module(types).
-compile(export_all).
-author( 'prataprc@gmail.com' ).

integer() ->
    [ {norm, 11111111111111}, {charnotat, $a}, {basenotat, 16#abcdef } ].

float() ->
    [ {decimal, 2.3}, {scientific, 2.3e3} ].

atom() ->
    [ alphanum, with_underscore@attherate ].

