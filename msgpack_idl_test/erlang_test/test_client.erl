
% This file is automatically generated by msgpack-idl.
-module(test_client).
-author('@msgpack-idl').

-include("test_types.hrl").
-export([connect/3, close/1]).



-export([get/2, set/3]).

-spec connect(inet:ip_address(), inet:port_number(), [proplists:property()]) -> {ok, pid()} | {error, any()}.
connect(Host,Port,Options)->
    msgpack_rpc_client:connect(tcp,Host,Port,Options).

-spec close(pid())-> ok.
close(Pid)->
    msgpack_rpc_client:close(Pid).


-spec get(pid(), mp_string()) -> mp_string().
get(Pid, Key) ->
    msgpack_rpc_client:call(Pid, get, [Key]).

-spec set(pid(), mp_string(), mp_string()) -> mp_string().
set(Pid, Key, Val) ->
    msgpack_rpc_client:call(Pid, set, [Key, Val]).


