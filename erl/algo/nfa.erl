-module(re).
-compile(export_all).

state( split, Outs ) -> { split, Out1, Out2 }
state( C, Out )     -> { C, Out1, Out2 }

frag( From, To ) ->

reduce( {

parsere([$||T], Stack) ->
parsere([$*|T], Stack) ->
parsere([$?|T], Stack) ->
parsere([$+|T], Stack) ->
parsere([C|T], Stack)  -> state( C, null, null )
