
// This file is auto-generated from test.idl
// *** DO NOT EDIT ***

#ifndef TEST_CLIENT_HPP_
#define TEST_CLIENT_HPP_


#include "test_types.hpp"
#include <msgpack/rpc/client.h>


namespace hoge {

namespace client {

class hoge {
public:
  hoge(const std::string &host, uint64_t port)
    : c_(host, port) {}

    std::string get(std::string key) {
      return c_.call("get", key).get<std::string >();
    }

    std::string set(std::string key, std::string val) {
      return c_.call("set", key, val).get<std::string >();
    }

private:
  msgpack::rpc::client c_;
};

} // namespace client

} // namespace hoge



#endif // TEST_CLIENT_HPP_
