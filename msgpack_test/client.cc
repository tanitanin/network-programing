#include <iostream>
#include <msgpack/rpc/client.h>

int main() {
  msgpack::rpc::client cli("localhost", 40320);
  std::string key("hoge");
  std::string val("hogehoge");
  std::cout << cli.call("set", key, val).get<bool>() << std::endl;
  std::string str = cli.call("get", key).get<std::string>();
  std::cout << str << std::endl;
}
