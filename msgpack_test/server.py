import msgpackrpc

class MyServer(object) :
  def __init__(self) :
    super(MyServer, self).__init__()
    self.kvs = {}
  
  def set(self, key, val):
    self.kvs[key] = val
  
  def get(self, key):
    try:
      return self.kvs[key]
    except KeyError:
      return None
  

if __name__ == "__main__":
  server = msgpackrpc.Server(MyServer())
  server.listen(msgpackrpc.Address('localhost', 40320))
  server.start()

