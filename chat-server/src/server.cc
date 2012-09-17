//

//-------------------------------------
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "server.h"
//-------------------------------------
//-------------------------------------
ChatServer::ChatServer(boost::asio::io_service& is,
                       const boost::asio::ip::tcp::endpoint& ep)
  : io_service_(is),
    acceptor_(is, ep)
{
  chat_session_ptr new_session(new ChatSession(io_service_, room_));
  acceptor_.async_accept(new_session->socket(),
      boost::bind(&ChatServer::handle_accept, this, new_session,
                  boost::asio::placeholders::error));
}
void ChatServer::handle_accept(chat_session_ptr session,
                               const boost::system::error_code& error)
{
  if(!error) {
    session->start();
    chat_session_ptr new_session(new ChatSession(io_service_, room_));
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&ChatServer::handle_accept, this, new_session,
                    boost::asio::placeholders::error));
  }
}
//-------------------------------------
