require 'msgpack/rpc'

cli = MessagePack::RPC::Client.new("localhost",40320)

# test
cli.call(:set,"hoge","hogehoge")
cli.call(:set,"foo","bar")

p cli.call(:get,"foo")
p cli.call(:get,"hugahuga")

