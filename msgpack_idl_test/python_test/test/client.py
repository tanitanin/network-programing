
# This file is auto-generated from test.idl
# *** DO NOT EDIT ***


import msgpackrpc
from types import *


class hoge:
  def __init__ (self, host, port):
    address = msgpackrpc.Address(host, port)
    self.client = msgpackrpc.Client(address)

  def get (self, key):
    retval = self.client.call('get', key)
    return retval

  def set (self, key, val):
    retval = self.client.call('set', key, val)
    return retval



