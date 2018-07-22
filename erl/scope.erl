-module(scope).

scope_check(I) ->
    {X,Y} = try is_integer(I) of
                true -> {10, 20};
                false -> {20, 10}
            catch
                Z -> erlang:display( Z )
            end,
    erlang:display({X, Y}).


main(Args) ->
    erlang:display(Args),
    scope_check(10),
    scope_check(ok).
