
// This file is auto-generated from test.idl
// *** DO NOT EDIT ***

#ifndef TEST_SERVER_HPP_
#define TEST_SERVER_HPP_


#include "test_types.hpp"
#include <msgpack/rpc/server.h>


namespace hoge {

namespace server {

template <class Impl>
class hoge : public msgpack::rpc::server::base {
public:

  void dispatch(msgpack::rpc::request req) {
    try {
      std::string method;
      req.method().convert(&method);

      if (method == "get") {
        msgpack::type::tuple<std::string > params;
        req.params().convert(&params);
        req.result<std::string >(static_cast<Impl*>(this)->get(params.get<0>()));
        return;
      }

      if (method == "set") {
        msgpack::type::tuple<std::string, std::string > params;
        req.params().convert(&params);
        req.result<std::string >(static_cast<Impl*>(this)->set(params.get<0>(), params.get<1>()));
        return;
      }

    } catch (const msgpack::type_error& e) {
      req.error(msgpack::rpc::ARGUMENT_ERROR);
    } catch (const std::exception& e) {
      req.error(std::string(e.what()));
    }
  }
};

} // namespace server

} // namespace hoge



#endif // TEST_SERVER_HPP_
