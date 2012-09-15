
#include <iostream>
#include <list>
#include <boost/asio.hpp>
#include "server.h"

using namespace std;

typedef boost::shared_ptr<ChatServer> chat_server_ptr;
typedef std::list<chat_server_ptr> chat_server_list;

int main(int argc, char **argv)
{
  try {
    boost::asio::io_service io_service;
    chat_server_list servers;
    boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), atoi("40320"));
    chat_server_ptr server(new ChatServer(io_service, endpoint));
    servers.push_back(server);
    io_service.run();
  } catch(std::exception& e) {
    std::cerr<< "Exception: " << e.what() << endl;
  }
  
  return 0;
}
