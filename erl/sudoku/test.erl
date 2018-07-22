-module(test).
-import(random, [seed/3, uniform/1]).
-import(lists).
-import(sudoku).
-include("sudoku.hrl").
-compile(export_all).

-record( testcase, { dimension, elimit, count } ).

d2_table()     -> {
                    { 0, 0, 0, 1 },
                    { 0, 0, 0, 0 },
                    { 0, 0, 0, 0 },
                    { 0, 0, 0, 0 }
                  }.

d3_table()     -> {
                    { 0, 0, 0, 0, 0, 0, 0, 0, 1 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0 }
                  }.

sample_table() -> { {  0,  1,  0,  0 },
                    {  2,  3,  0,  0 },
                    {  0,  0,  0,  0 },
                    {  1,  0,  0,  0 }
                  }.

sample_repeat() -> [ [ 1,2,3,4,5],
                     [ 1,1,2,3,3],
                     [ 1,2,3,4,4]
                   ].

tcases_generate() ->
    [ #testcase{ dimension=3, elimit=27, count=10 },
      #testcase{ dimension=3, elimit=29, count=10 },
      #testcase{ dimension=3, elimit=31, count=10 },
      #testcase{ dimension=3, elimit=33, count=10 },
      #testcase{ dimension=3, elimit=35, count=10 },
      #testcase{ dimension=3, elimit=37, count=10 },
      #testcase{ dimension=4, elimit=100, count=10 },
      #testcase{ dimension=4, elimit=105, count=10 },
      #testcase{ dimension=4, elimit=110, count=10 },
      #testcase{ dimension=4, elimit=120, count=10 },
      #testcase{ dimension=4, elimit=130, count=10 }
    ].


test( generate, #testcase{ dimension=D, elimit=L }=Tc, Count ) ->
    Tb = sudoku:generate( D, L ),
    sudoku:validate( gentime, Tb ),
    case sudoku:validate( gentime, Tb ) of
        true  -> true;
        false -> io:format("Failed Test case: ~w (Count ~w) ~nTable : ~w ~n",
                           [ Tc, Count, Tb ]), false
    end.


test( nthcol )       -> sudoku:nthcol( 2, sample_table() );
test( flattable )    -> sudoku:flattable( 2, sample_table() );
test( subtab )       -> sudoku:subtab( asflis, 2, 1, sample_table() );
test( subtabrc )     -> [ sudoku:subtabrc( 3, I ) || I <- lists:seq( 0, 8 ) ];
test( isrepeat )     -> [ sudoku:is_repeat( juxtapose, L ) || L <- sample_repeat() ];
test( ecount )       -> sudoku:ecount( intable, 2, sample_table() );
test( genvalidate )  -> Tb_init = #table{ dimension=2, 
                                          table=sample_table(),
                                          r=1,
                                          c=1,
                                          count=0,
                                          rules=#rules{ elimit=8 }
                                        },
                        sudoku:validate( gentime, Tb_init );
test( tblelement )   -> sudoku:tblelement( sample_table(), 4, 2 );
test( update_table ) -> sudoku:tblelement(
                            sudoku:update_table( sample_table(), 2, 2, [1,2]),
                            2, 2 );
test( init_table )   -> sudoku:init_table( 4 );
test( fixedelements )-> [ sudoku:fixedelements( tuple_to_list( R )) 
                          || R <- tuple_to_list( sample_table() ) ];
test( init_reduce )  -> sudoku:init_reduce( 2, sample_table() );
test( rr_byrow )     -> sudoku:rr_byrow( 2, sudoku:init_reduce( 2, sample_table() ));
test( rr_bycol )     -> sudoku:rr_bycol( 2, sudoku:init_reduce( 2, sample_table() ));
test( rr_bystb )     -> sudoku:rr_bystb( 2, sudoku:init_reduce( 2, sample_table() ));
test( rr_by )        -> sudoku:rr_bystb( 2, 
                            sudoku:rr_bycol( 2, 
                                sudoku:rr_byrow( 2, sudoku:init_reduce( 2, sample_table() ))
                        ));
test( find_unique )  -> [ sudoku:find_unique( tuple_to_list( element( R, test( rr_by )))) 
                          || R <- lists:seq( 1, 4 ) ];
test( rr_urow )      -> sudoku:rr_uniqinrow( 2, test( rr_by ));
test( rr_ucol )      -> sudoku:rr_uniqincol( 2, test( rr_by ));
test( rr_ustb )      -> sudoku:rr_uniqinstb( 2, test( rr_by ));
test( rr_uniq )      -> sudoku:rr_uniqinrow( 2, 
                            sudoku:rr_uniqincol( 2, 
                                sudoku:rr_uniqinstb( 2, test( rr_by ))
                        ));
test( rr_fix  )      -> sudoku:rr_fix( 2, test( rr_uniq ));
test( reduce )       -> sudoku:reduce( 2, sudoku:init_reduce( 2, sample_table() ),
                                       sudoku:reducerules() );

test( gencases )     -> lists:all( 
                            fun( X ) -> X end,
                            [ test( generate, Tc, Count ) ||
                                #testcase{}=Tc <- tcases_generate(),
                                Count <- lists:seq( 1, Tc#testcase.count ) ]
                        );

test( backtrack )    -> sudoku:backtrack( reduce, 2, sudoku:init_reduce( 2, sample_table() ), 1, 1 );

test( solve )        -> Tbs = [ sudoku:generate( 3, 20 ) || _I <- lists:seq(1,1)  ],
                        sudoku:print_table( 3, (lists:nth( 1, Tbs ))#table.table),
                        [ sudoku:solve( 3, Table ) || #table{table=Table}=_Tb <- Tbs ];

test( d3 )           -> sudoku:solve( 3, d3_table() );

test( d2 )           -> sudoku:solve( 2, d2_table() ).


tcases_2D() -> [ { 2, 8,  10 }, { 2, 7,  10 }, { 2, 6,  10 }, { 2, 4,  10 } ].
tcases_3D() -> [ { 3, 35, 10 }, { 3, 31, 10 }, { 3, 27, 10 }, { 3, 20, 10 } ].
tcases_4D() -> [ { 4, 110, 10 }, { 4, 105, 10 }, { 4, 100, 10 }, { 4, 85, 10 } ].

tcases_full() -> tcases_2D() ++ tcases_3D() ++ tcases_4D().

testfull( { D, Elimit, 0 }, PCount, FCount ) -> 
    io:format("Completed ~w dimension sudoku with Elimit, ~w ~n", [D,Elimit]),
    io:format("Passed ... ~w ~n", [PCount] ),
    io:format("Failed ... ~w ~n", [FCount] ),
    { PCount, FCount };

testfull( { D, Elimit, Count }, PCount, FCount ) ->
    #table{ table=Table }=_Tb = sudoku:generate( D, Elimit ),
    case sudoku:solve( D, Table ) of
        { passed, _Tb_new } -> testfull( { D, Elimit, Count-1 }, PCount+1, FCount );
        { failed, _Tb_new } -> testfull( { D, Elimit, Count-1 }, PCount, FCount+1 )
    end.

testfull() -> [ testfull( Tcase, 0, 0 ) || Tcase <- tcases_2D() ].

