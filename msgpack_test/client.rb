require 'msgpack/rpc'

cli = MessagePack::RPC::Client.new("localhost",40320)

# test
key = "hoge"
val = "hogehoge"
cli.call(:set,key,val)
p "called"
cli.call(:set,"foo","bar")
p "called"

p cli.call(:get,"foo")
p cli.call(:get,"hugahuga")

