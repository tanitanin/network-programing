//

#ifndef __CHAT_SERVER_H__
#define __CHAT_SERVER_H__

//-------------------------------------
#include <iostream>
#include <boost/asio.hpp>
#include "chat.h"
//-------------------------------------
class ChatServer
{
pivate:
  boost::asio::io_service& io_service_;
  boost::asio::ip::tcp::acceptor acceptor_;
  ChatRoom room_;
public:
  ChatServer(boost::asio::io_service& is, boost::asio::ip::tcp::endpoint& ep);
  void handle_accept(boost::system::error_code&);
};
//-------------------------------------

#endif /* __CHAT_SERVER_H__ */
