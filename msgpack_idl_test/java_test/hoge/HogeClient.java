
// This file is auto-generated from test.idl
// *** DO NOT EDIT ***


package hoge;



import org.msgpack.rpc.Client;
import org.msgpack.rpc.loop.EventLoop;

public class HogeClient {
  public HogeClient(String host, int port, double timeout_sec) throws Exception {
    EventLoop loop = EventLoop.defaultEventLoop();
    c_ = new Client(host, port, loop);
    iface_ = c_.proxy(RPCInterface.class);
  }

  public static interface RPCInterface {
    String get(String key);
    String set(String key, String val);

  }


  public String get(String key) {
    return iface_.get(key);
  }

  public String set(String key, String val) {
    return iface_.set(key, val);
  }

  private Client c_;
  private RPCInterface iface_;
};


