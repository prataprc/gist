% Communicate mappings from <protocol, address> pairs to 48.bit

% ARP packer format.
%
% 16.bit: (ar$hrd) Hardware address space (e.g., Ethernet,
% 		  Packet Radio Net.)
% 16.bit: (ar$pro) Protocol address space.  For Ethernet
% 		  hardware, this is from the set of type
% 		  fields ether_typ$<protocol>.
%  8.bit: (ar$hln) byte length of each hardware address
%  8.bit: (ar$pln) byte length of each protocol address
% 16.bit: (ar$op)  opcode (ares_op$REQUEST | ares_op$REPLY)
% nbytes: (ar$sha) Hardware address of sender of this
% 		  packet, n from the ar$hln field.
% mbytes: (ar$spa) Protocol address of sender of this
% 		  packet, m from the ar$pln field.
% nbytes: (ar$tha) Hardware address of target of this
% 		  packet (if known).
% mbytes: (ar$tpa) Protocol address of target.

-compile(export_all).
-define(HOSTMAC, <<16#00,16#1c,16#c0,16#f3,16#17,16#5>>).

hostmac() -> ?HOSTMAC.

arp_request()

arp_reply()

pa2ha( {ProtocolType, ProtocolAddr} ) -> HwAddr.
