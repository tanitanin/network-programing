require 'rubygems'
require 'msgpack/rpc'

class MyServer
  def initialize
    @kvs = {}
  end
  
  def set(key, val)
    @kvs[key] = val
    nil
  end
  
  def get(key)
    @kvs[key]
  end
end

svr = MessagePack::RPC::Server.new
svr.listen "localhost", 40320, MyServer.new
svr.run

