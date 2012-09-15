//

#ifndef __CHAT_SERVER_H__
#define __CHAT_SERVER_H__

//-------------------------------------
#include <iostream>
#include <boost/asio.hpp>
#include "chat.h"
//-------------------------------------
typedef boost::shared_ptr<ChatSession> chat_session_ptr;
//-------------------------------------
class ChatServer
{
private:
  boost::asio::io_service& io_service_;
  boost::asio::ip::tcp::acceptor acceptor_;
  ChatRoom room_;
public:
  ChatServer(boost::asio::io_service& is, const boost::asio::ip::tcp::endpoint& ep);
  void handle_accept(chat_session_ptr,const boost::system::error_code&);
};
//-------------------------------------

#endif /* __CHAT_SERVER_H__ */
