-module(sudoku).
-import(random, [seed/3, uniform/1]).
-import(lists).
-include("sudoku.hrl").
-compile(export_all).

%%%% Helper logics %%%%

%% Seeding the random number generator.
print_table( D, Table ) ->
    [ io:format("~w~n", [element(I,Table)] ) || I <- lists:seq(1,D*D) ],
    io:format("~n").

seedtable() -> {A1, A2, A3} = now(),
               seed( A1, A2, A3 ), {A1,A2,A3}.

seedtable( { A1, A2, A3 }=Seed ) -> seed( A1, A2, A3 ), 
                                    Seed.


%% Get nth column from Table
nthcol( N, Table ) -> [ element( N, Row ) || Row <- tuple_to_list( Table ) ].


%% Flatten the entire Table 
flattable( D, Table ) ->
    lists:flatten([ tuple_to_list( element( R, Table )) || R <- lists:seq( 1, D*D ) ]).


%% Get sub-table matrix.
subtabr( aslist, { From, To }, Row ) ->
    [ element( N, Row ) || N <- lists:seq( From, To ) ];
subtabr( astupl, { From, To }, Row ) ->
    list_to_tuple(subtabr( aslist, { From, To }, Row )).

subtab( Aswhat, { D, N, Table } ) ->                    %% N starts from 0
    From = ((N div D) * D) + 1,
    To   = From+D-1,
    Col  = ((N rem D) * D) + 1,
    [ subtabr( Aswhat, { Col, Col+D-1 }, element( X, Table ))
      || X <- lists:seq( From, To ) ].
subtab( aslist, D, N, Table )   ->                      %% sub-table as list
    subtab( aslist, { D, N, Table } );
subtab( asflis, D, N, Table ) ->                        %% sub-table as flatlist
    [ E || RList <- subtab( aslist, { D, N, Table } ), E <- RList ];
subtab( astupl, D, N, Table )  ->                       %% sub-table as tuple
    subtab( astupl, { D, N, Table } ).

%% Calculate the {R,C} tuple for each element in the subtable N
subtabrc( D, _, Count, Res ) when Count =:= (D*D) -> Res;
subtabrc( D, N, Count, Res ) ->
    subtabrc( D, N, Count+1, 
              [ { (((N div D) *D) +1) + (Count div D),
                  (((N rem D) *D) +1) + (Count rem D)
                } | Res 
              ]
            ).

subtabrc( D, N ) -> lists:reverse( subtabrc( D, N, 0, [] )).

%% Whether the adjusant elements are same.
is_repeat( juxtapose, [], _ )    -> false;
is_repeat( juxtapose, [H|T], 0 ) -> is_repeat( juxtapose, T, H );
is_repeat( juxtapose, [H|_], H ) -> true;
is_repeat( juxtapose, [H|T], _ ) -> is_repeat( juxtapose, T, H ).
is_repeat( juxtapose, [H|T] )    -> is_repeat( juxtapose, T, H ).


%% Count valid elements in the table
ecount( inrow, [], Acc )    -> Acc;
ecount( inrow, [0|T], Acc ) -> ecount( inrow, T, Acc );
ecount( inrow, [_|T], Acc ) -> ecount( inrow, T, Acc+1 );
ecount( intable, D, Table ) -> lists:sum([
                                    ecount( inrow, tuple_to_list(element( I, Table )), 0) 
                                    || I <- lists:seq( 1, D*D ) ]
                               ).


%% Validate logic
validate( gentime, #table{ dimension=D, table=Table, rules=Rules }=_Tb ) ->
    not ( ( ecount( intable, D, Table ) =/= Rules#rules.elimit )
          or
          lists:any(
              fun( X ) -> X end,
              [ is_repeat( juxtapose, lists:sort(tuple_to_list(element( I, Table ))), -1 )
                || I <- lists:seq( 1, D*D ) ]
          )
          or
          lists:any(
              fun( X ) -> X end,
              [ is_repeat( juxtapose, lists:sort(nthcol( I, Table )), -1 )
                || I <- lists:seq( 1, D*D ) ]
          )
          or
          lists:any(
              fun( X ) -> X end,
              [ is_repeat( juxtapose, lists:sort(subtab( asflis, D, I, Table )), -1 )
                || I <- lists:seq( 0, (D*D)-1 ) ]
          )
        ).


validate( fixtime, D, Table ) ->
    Seq = lists:seq( 1, D*D ),
    lists:all( fun( X ) -> is_integer( X ) end, flattable( D, Table ) )
    and
    lists:all( fun(X) -> X end, 
               [ Seq =:= lists:sort( tuple_to_list (element( R, Table )) ) || R <- Seq ]
             )
    and
    lists:all( fun(X) -> X end, 
               [ Seq =:= lists:sort( nthcol( C, Table )) || C <- Seq ]
             )
    and
    lists:all( fun(X) -> X end, 
               [ Seq =:= lists:sort( subtab( asflis, D, I, Table ))
                 || I <- lists:seq( 0, (D*D)-1 ) ]
             ).


%% Fetch Table element.
tblelement( Table, R, C ) -> element( C, element( R, Table )).


%% Update Table element.
update_table( Table, R, C, E ) ->
    setelement( R, Table, setelement( C, element( R, Table ), E )).


%% Initialise table
init_row( D )   -> list_to_tuple([ 0 || _ <- lists:seq( 1, D ) ]).
init_table( D ) -> list_to_tuple([ init_row( D ) || _ <- lists:seq( 1, D ) ]).


%%%% Puzzle generators %%%%

%% Skip rules
sr_countlimit( #table{ count=Count, rules=Rules }=_Tb ) ->
    if 
        Count < Rules#rules.elimit -> false;
        true -> true
    end.



sr_random( #table{ dimension=D, rules=Rules }=_Tb ) ->
    random:uniform( D * D * D * D ) > Rules#rules.elimit .


%% List of Skip-Rule functors 
skiprules() -> [ fun sr_countlimit/1, fun sr_random/1 ].


%% Pick rules
pr_row( E, #table{ table=Table, r=R }=_Tb ) ->
    not lists:any( fun( X ) -> X == E end, tuple_to_list(element( R, Table )) ).


pr_col( E, #table{ table=Table, c=C }=_Tb ) ->
    not lists:any( fun( X ) -> X == E end, nthcol( C, Table ) ).


pr_stb( E, #table{ dimension=D, table=Table, r=R, c=C }=_Tb ) ->
    N = (((R-1) div D) * D) + ((C-1) div D),    % Nth sub table, from 0.
    not lists:any( fun( X ) -> X == E end, subtab( asflis, D, N, Table )).


%% List of Pick-Rule functors 
pickrules() ->  [ fun pr_row/2, fun pr_col/2, fun pr_stb/2 ].


%%  Pick element.
pick_number( #table{}=_Tb, [] )    -> { new, 0 }; %% TODO : This can be a failure case
pick_number( #table{}=Tb,  [H|T] ) ->
    case lists:all( fun( F ) -> F( H, Tb ) end, pickrules() ) of
        true  -> H;
        false -> pick_number( Tb, T )
    end.

pick_number( #table{ dimension=D, table=Table, r=R, c=C }=Tb ) ->
    case tblelement( Table, R, C ) of   %% Fetch the table element
        0 -> 
            case lists:any( fun( F ) -> F( Tb ) end, skiprules() ) of
                true  -> { new, 0 };
                false -> { new, pick_number( Tb, lists:seq(1, D*D) ) }
            end;
        N when N > 0 -> 
            { old, N }
    end.


gen_row( #table{ dimension=D, c=C }=Tb ) when C > (D*D)    -> Tb;
gen_row( #table{ table=Table, r=R, c=C, count=Count }=Tb ) ->
    case pick_number( Tb ) of
        { new, 0 } ->
            gen_row( Tb#table{ table=update_table( Table, R, C, 0 ), c=C+1 });
        { new, Element } ->
            gen_row( Tb#table{ table=update_table( Table, R, C, Element ), c=C+1, count=Count+1 });
        { old, Element } ->
            gen_row( Tb#table{ table=update_table( Table, R, C, Element ), c=C+1 })
    end.


gen_rows( #table{ dimension=D, r=R }=Tb ) when R > (D*D) -> Tb;
gen_rows( #table{ r=R }=Tb ) ->
    gen_rows( (gen_row( Tb#table{ c=1 } ))#table{ r=R+1 } ).


gen_table( #table{}=Tb, 0 )     -> Tb;
gen_table( #table{ dimension=D, rules=Rules }=Tb, Times ) ->
    Tb_new = gen_rows( Tb#table{ r=1, c=1 } ),
    case ( ecount( intable, D, Tb_new#table.table ) =:= Rules#rules.elimit ) of
        true  -> Tb_new;
        false -> gen_table( Tb_new, Times - 1 )
    end.


%%%% Puzzle solvers %%%%

%% Collect all the elements that are identified in the List.
fixedelements( L ) -> [ X || X <- L, X =/= 0 andalso is_integer( X )  ].


%% Initialize the table, with un-identified element in the table with a list 
%% of all possible elements.
init_reduce( D, Table, R, _, _Allpos ) when R > (D*D) -> Table;
init_reduce( D, Table, R, C, Allposs ) when C > (D*D) ->
    init_reduce( D, Table, R+1, 1, Allposs );
init_reduce( D, Table, R, C, Allposs ) when (C =< (D*D)) and (R =< (D*D)) ->
    case tblelement( Table, R, C ) of
        0 -> 
            Tb_new = update_table( Table, R, C, Allposs ),
            init_reduce( D, Tb_new, R, C + 1, Allposs );
        N when N =< (D*D) ->
            init_reduce( D, Table, R, C + 1, Allposs )
    end.

init_reduce( D, Table ) -> init_reduce( D, Table, 1, 1, lists:seq( 1, D*D ) ).
    

%% Rule to reduce the possible list of elements in relation to row.
rr_byrow( D, Table, R, _, _Fixedrws ) when R > (D*D) -> Table;
rr_byrow( D, Table, R, C, Fixedrows ) when C > (D*D) ->
    rr_byrow( D, Table, R+1, 1, Fixedrows );
rr_byrow( D, Table, R, C, Fixedrows ) ->
    E = tblelement( Table, R, C ),
    if 
        is_list( E ) ->
            Rowelem = element( R, Fixedrows ),
            rr_byrow( D, update_table( Table, R, C, E -- Rowelem ), R, C+1, Fixedrows );
        true ->
            rr_byrow( D, Table, R, C+1, Fixedrows )
    end.

rr_byrow( D, Table ) ->
    Fixedrows = list_to_tuple([ fixedelements( tuple_to_list( element( R, Table )))
                                || R <- lists:seq( 1, D*D ) ]),
    rr_byrow( D, Table, 1, 1, Fixedrows ).


%% Rule to reduce the possible list of elements in relation to column.
rr_bycol( D, Table, R, _, _Fixedcls ) when R > (D*D) -> Table;
rr_bycol( D, Table, R, C, Fixedcols ) when C > (D*D) ->
    rr_bycol( D, Table, R+1, 1, Fixedcols );
rr_bycol( D, Table, R, C, Fixedcols ) ->
    E = tblelement( Table, R, C ),
    if 
        is_list( E ) ->
            Colelem = element( C, Fixedcols ),
            rr_bycol( D, update_table( Table, R, C, E -- Colelem ), R, C+1, Fixedcols );
        true ->
            rr_bycol( D, Table, R, C+1, Fixedcols )
    end.

rr_bycol( D, Table ) ->
    Fixedcols = list_to_tuple([ fixedelements( nthcol( C, Table )) 
                                || C <- lists:seq( 1, D*D ) ]),
    rr_bycol( D, Table, 1, 1, Fixedcols ).


%% Rule to reduce the possible list of elements in relation to column.
rr_bystb( D, Table, R, _, _Fixdstbs ) when R > (D*D) -> Table;
rr_bystb( D, Table, R, C, Fixedstbs ) when C > (D*D) ->
    rr_bystb( D, Table, R+1, 1, Fixedstbs );
rr_bystb( D, Table, R, C, Fixedstbs ) ->
    E = tblelement( Table, R, C ),
    if 
        is_list( E ) ->
            N       = (((R-1) div D) * D) + ((C-1) div D), % Nth sub table, from 0.
            Stbelem = element( N+1, Fixedstbs ),
            rr_bystb( D, update_table( Table, R, C, E -- Stbelem ), R, C+1, Fixedstbs );
        true ->
            rr_bystb( D, Table, R, C+1, Fixedstbs )
    end.

rr_bystb( D, Table ) ->
    Fixedstbs = list_to_tuple([ fixedelements( subtab( asflis,  D, I, Table ))
                                || I <- lists:seq( 0, (D*D)-1 ) ]),
    rr_bystb( D, Table, 1, 1, Fixedstbs ).


%% When a possible combination is unique for a given slot, either row-wise or
%% col-wise or subtable-wise, identify them.
find_unique( Plist, [] )                      -> Plist;
find_unique( Plist, [H|T] ) when is_list( H ) -> find_unique( Plist -- H, T );
find_unique( Plist, [_|T] )                   -> find_unique( Plist, T ).

find_unique( _,     [],    Res ) -> lists:reverse( Res );
find_unique( Upper, [H|T], Res ) ->
    if 
        is_integer( H ) -> find_unique( Upper, T, [[]|Res] );
        is_list( H )    -> find_unique( [H|Upper], T, 
                                        [find_unique( H, Upper ++ T ) | Res]
                                      )
    end.

find_unique( List ) -> find_unique( [], List, [] ).


%% For all the identified unique possibility, fix the elements in its slots.
update_unique( Table, [] )               -> Table;
update_unique( Table, [{R,C,[E|[]]}|T] ) -> update_unique( update_table( Table, R, C, [E] ), T );
update_unique( Table, [{_,_,_}|T] )      -> update_unique( Table, T ).


%% Rule to reduce the table by identifying the unique possible element row-wise.
rr_uniqinrow( D, Table, R ) when R > (D*D) -> Table;
rr_uniqinrow( D, Table, R ) ->
    rr_uniqinrow( D, 
                  update_unique( Table,
                                 lists:zip3( lists:duplicate( D*D, R ),
                                             lists:seq( 1, D*D ),
                                             find_unique( tuple_to_list( element( R, Table ))) 
                                           )
                               ),
                  R+1
                ).

rr_uniqinrow( D, Table ) -> rr_uniqinrow( D, Table, 1 ).
    

%% Rule to reduce the table by identifying the unique possible element row-wise.
rr_uniqincol( D, Table, C ) when C > (D*D) -> Table;
rr_uniqincol( D, Table, C ) ->
    rr_uniqincol( D,
                  update_unique( Table,
                                 lists:zip3( lists:seq( 1, D*D ),
                                             lists:duplicate( D*D, C ),
                                             find_unique( nthcol( C, Table ))
                                           )
                               ),
                  C+1
                ).

rr_uniqincol( D, Table ) -> rr_uniqincol( D, Table, 1 ).
    

%% Rule to reduce the table by identifying the unique possible element row-wise.
rr_uniqinstb( D, Table, I ) when I > ((D*D)-1) -> Table;
rr_uniqinstb( D, Table, I ) ->
    rr_uniqinstb( D,
                  update_unique( Table,
                                 lists:zipwith( fun( {R, C}, E ) -> {R,C,E} end,
                                                subtabrc( D, I ),
                                                find_unique( subtab( asflis, D, I, Table ))
                                              )
                               ),
                  I+1
                ).

rr_uniqinstb( D, Table ) -> rr_uniqinstb( D, Table, 0 ).
    

%% After all the reduction algorithms, if there is only one possible element
%% in any given slot then fix the element in the slot.
rr_fix( D, Table, R, _, State ) when R > (D*D) ->
    { State, Table };
rr_fix( D, Table, R, C, State ) when C > (D*D) ->
    rr_fix( D, Table, R+1, 1, State );
rr_fix( D, Table, R, C, State ) ->
    case tblelement( Table, R, C ) of
        [E|[]]                 -> rr_fix( D, update_table( Table, R, C, E ), R, C+1, fixed );
        E when is_integer( E ) -> rr_fix( D, Table, R, C+1, State );
        [_|T] when T =/= []    -> rr_fix( D, Table, R, C+1, State );
        []                     -> { notfixed, Table }
    end.

rr_fix( D, Table ) -> rr_fix( D, Table, 1, 1, notfixed ).


%% List of Reduction-Rule functors 
reducerules() -> [ fun rr_byrow/2, fun rr_bycol/2, fun rr_bystb/2,
                   fun rr_uniqinrow/2, fun rr_uniqincol/2, fun rr_uniqinstb/2
                 ].


%% Repeated reduction until no more slots can be fixed using the functor rules.
reduce( D, Table, [] ) ->
    case rr_fix( D, Table ) of
        { notfixed, Tb_new } -> Tb_new;
        { fixed,    Tb_new } -> reduce( D, Tb_new, reducerules() ) %% Re-run
    end;
reduce( D, Table, [Fun|T] ) -> reduce( D, Fun( D, Table ), T ).


%% The back-track algorithm to solve the sudoku puzzle. A double recursive
%% algorithm that takes more effort to learn, take your time !!
backtrack( elist, _, Table, _, _, [] )    -> { failed, Table };
backtrack( elist, D, Table, R, C, [E|T] ) ->
    Tnew = update_table( Table, R, C, E ),
    case backtrack( reduce, D, Tnew, R, C+1 ) of
        { failed, _Tb_new } -> backtrack( elist, D, Table, R, C, T );
        { passed, Tb_new } -> { passed, Tb_new }
    end;
backtrack( elist, D, Table, R, C, _ )     -> backtrack( noreduce, D, Table, R, C+1 ).

backtrack( _,    D, Table, R, _ ) when R > (D*D) -> { failed, Table };
backtrack( Atom, D, Table, R, C ) when C > (D*D) ->
    backtrack( Atom, D, Table, R+1, 1 );
backtrack( reduce, D, Table, R, C ) ->
    Tnew = reduce( D, Table, reducerules() ),
    %% print_table( D, Table ),
    case validate( fixtime, D, Tnew ) of
        true  -> { passed, Tnew };
        false -> backtrack( elist, D, Tnew, R, C, tblelement( Tnew, R, C ))
    end;
backtrack( noreduce, D, Table, R, C ) ->    %% Skip reduce / validate steps
    backtrack( elist, D, Table, R, C, tblelement( Table, R, C )).

%%%% Application APIs %%%%

%% Generate a sudoku puzzle.
generate( D, Elimit ) ->
    Tb_init = #table{ dimension=D, 
                      table=init_table( D*D ),
                      r=1,
                      c=1,
                      count=0,
                      rules=#rules{ elimit=Elimit }
                    },
    _Seed   = seedtable(),
    gen_table( Tb_init, 5 ).


%% Solve a sudoku puzzle.
solve( D, Table ) ->
    backtrack( reduce, D, init_reduce( D, Table ), 1, 1 ).
