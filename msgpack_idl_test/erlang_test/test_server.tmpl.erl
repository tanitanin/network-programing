
% This file is auto-generated from test.idl



-module(test_server).
-author('@msgpack-idl').

-include("test_types.hrl").



-export([get/1, set/2]).


-spec get(mp_string()) -> mp_string().
get(Key) ->
  Reply = <<"ok">>,  % write your code here
  Reply.

-spec set(mp_string(), mp_string()) -> mp_string().
set(Key, Val) ->
  Reply = <<"ok">>,  % write your code here
  Reply.



