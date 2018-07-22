-module(emath).
-export([ is_div2/1 ]).

%% Divisibility
is_div2( X ) -> (X band 1) == 0.
is_div2( X, N ) -> (X band N-1) == 0.
