-module(ethframe).
-export([ vlan_encode/3, vlan_decode/1, dec/1, enc/1 ]).
-include("ethframe.hrl").

%%---- Ethernet frame format
%   Preamble                            7 Octects
%   Start of frame delimiter            1 Octect
% Header
%   MAC destination                     6 Octects
%   MAC source                          6 Octects
%   802.1Q tag (optional)               4 Octects
%   Ethertype or length                 2 Octects
%
%   Payload                             46-1500 Octects
%
%   Frame check sequence (32-bit CRC)   4 Octects
%   Interframe gap                      12 Octects

% TODO :
%   1. Learn more about VLAN.

-define( VLANID, 16#8100 ).

vlan_encode( PCP, CFI, VID ) ->
    <<?VLANID:16,PCP:3,CFI:1,VID:12>>.

vlan_decode( <<?VLANID:16,PCP:3,CFI:1,VID:12>> ) ->
    {PCP,CFI,VID};
vlan_decode( _ ) ->
    false.

% TODO : Catch all clause, on production system this must log error.
%dec( <<S:48/bitstring,D:48/bitstring,Rest/bitstring>> ) ->
%    { eth, S, D, Rest };
dec( <<S:48/bitstring,D:48/bitstring,?VLANID:16,TCI:16,L:16,T:16,Rest/bitstring>> ) when L < 16#0600->
    <<P:L,C:32>> = Rest,
    #eth{ src=S, dest=D, tci=TCI, len=L, type=T, payload=P, crc=C };
dec( <<S:48/bitstring,D:48/bitstring,?VLANID:16,TCI:16,T:16,P:(1496*8)/bitstring,C:32>> ) ->
    #eth{ src=S, dest=D, tci=TCI, type=T, payload=P, crc=C };
dec( <<S:48/bitstring,D:48/bitstring,L:16,T:16,Rest/bitstring>> ) when L < 16#0600->
    <<P:L,C:32>> = Rest,
    #eth{ src=S, dest=D, len=L, type=T, payload=P, crc=C };
dec( <<S:48/bitstring,D:48/bitstring,T:16,P:(1496*8)/bitstring,C:32>> ) ->
    #eth{ src=S, dest=D, type=T, payload=P, crc=C }.

enc( #eth{tci=false,len=false}=E ) ->
    #eth{ src=S, dest=D, type=T, payload=P, crc=C } = E,
    <<S:48,D:48,T:16,P/bitstring,C:32>>;
enc( #eth{tci=false}=E ) ->
    #eth{ src=S, dest=D, len=L, type=T, payload=P, crc=C } = E,
    <<S:48,D:48,L:16,T:16,P/bitstring,C:32>>;
enc( #eth{len=false}=E ) ->
    #eth{ src=S, dest=D, tci=TCI, type=T, payload=P, crc=C } = E,
    <<S:48,D:48,?VLANID:16,TCI:16,T:16,P/bitstring,C:32>>;
enc( E ) ->
    #eth{ src=S, dest=D, tci=TCI, len=L, type=T, payload=P, crc=C } = E,
    <<S:48,D:48,?VLANID:16,TCI:16,L:16,T:16,P/bitstring,C:32>>.
