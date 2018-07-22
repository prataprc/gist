%% Record 'optdef' explanation.
%%
%% type     string(), int(), float(), bool()
%%          Type of the option value that will returned in 'option' record's
%%          value field.
%%
%% optname  atom()
%%          atom name that will be returned in 'option' record's optname.
%%
%% flag     string() -f[val] or --flag [val]
%%          option flag
%%          
%% default  term()
%%          default value for 'optname'
%%
%% action   store | store_false | store_true
%%          one of the above atoms, where
%%          store       -> Try to extract the value from arguments and store it.
%%          store_false -> If the flag is detected then store 'false'.
%%          store_true  -> If the flag is detected then store 'false'.
%%
%% help     string()
%%          Help string.
%%  
%% metavar  Meta-variable that symbolically denotes the value. Displayed in
%           the usage string.

-record(
    optdef,
    { type, optname, flags, default, action, help, metavar }
).

%% Record 'option' explanation.
%%
%% optname  atom()
%%          option name that was detected or defaulted.
%%
%% value    term()
%%          value of the option.

-record(
    option,
    { optname, value }
)
