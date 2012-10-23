#include <iostream>
#include <map>
#include <msgpack/rpc/server.h>
#include <msgpack/rpc/client.h>

class myserver : public msgpack::rpc::dispatcher {
private:
  std::map<std::string,std::string> kvs;
  
public:
  myserver() {
    kvs = std::map<std::string,std::string>();
  }
  
public:
  void set(msgpack::rpc::request req, const std::string& key, std::string& val) {
    //kvs[key] = val;
    kvs.insert(std::map<std::string,std::string>::value_type(key,val));
    std::cerr << ": set:" << key << " " << val << std::endl;
    req.result(true);
  }
  
  void get(msgpack::rpc::request req, const std::string& key) {
    std::cerr << ": get:" << key << std::endl;
    req.result(kvs[key]);
  }
  
public:
  void dispatch(msgpack::rpc::request req)
  try {
    std::string method;
    req.method().convert(&method);
    
    if(method == "set") {
      msgpack::type::tuple<std::string,std::string> params;
      req.params().convert(&params);
      set(req, params.get<0>(), params.get<1>());
    }
    else if(method == "get") {
      msgpack::type::tuple<std::string> params;
      req.params().convert(&params);
      get(req, params.get<0>());
    }
    else {
      req.error(msgpack::rpc::NO_METHOD_ERROR);
    }
  }
  catch(msgpack::type_error& e) {
    req.error(msgpack::rpc::ARGUMENT_ERROR);
    return;
  }
  catch(std::exception& e) {
    req.error(std::string(e.what()));
    return;
  }
  
};

int main() {

  msgpack::rpc::server svr;
  std::auto_ptr<msgpack::rpc::dispatcher> dp(new myserver);
  svr.serve(dp.get());
  svr.listen("localhost", 40320);
  svr.start(4);
  
  while(1);
}
