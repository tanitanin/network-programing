# This file is auto-generated from test.idl
# *** DO NOT EDIT ***

require 'rubygems'
require 'msgpack/rpc'
require File.join(File.dirname(__FILE__), 'types')

module MessagePack
module Client

class Hoge
  def initialize(host, port)
    @cli = MessagePack::RPC::Client.new(host, port)
  end
  def get(key)
    @cli.call(:get, key)
  end
  def set(key, val)
    @cli.call(:set, key, val)
  end
end

end
end
