//

#ifndef __CHAT_H__
#define __CHAT_H__

//-------------------------------------
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <set>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
//-------------------------------------
class ChatMessage
{
public:
  enum {header_length = 4};
  enum {max_body_length = 512};
private:
  char data_[header_length + max_body_length];
  size_t body_length_;
public:
  ChatMessage(): body_length_(0) {}
  const char *data() const { return data_; }
  char *data() { return data_; }
  size_t length() const { return header_length + body_length_; }
  char *body() { return data_ + header_length; }
  size_t body_length() const { return body_length_; }
  void body_length(size_t length);
  bool decode_header();
  void encode_header();
};

//-------------------------------------
class ChatParticipant
{
public:
  virtual ~ChatParticipant(){}
  virtual void deliver(const ChatMessage& msg) = 0;
};

typedef boost::shared_ptr<ChatParticipant> chat_participant_ptr;
//-------------------------------------
class ChatRoom
{
private:
  std::set<chat_participant_ptr> participants_;
  enum { max_recent_msgs =  100 };
  std::deque<ChatMessage> recent_msgs_;
public:
  void join(chat_participant_ptr);
  void leave(chat_participant_ptr);
  void deliver(const ChatMessage&);
};

//-------------------------------------
class ChatSession
  : public ChatParticipant,
    public boost::enable_shared_from_this<ChatSession>
{
private:
  boost::asio::ip::tcp::socket socket_;
  ChatRoom& room_;
  ChatMessage read_msg_;
  std::deque<ChatMessage> write_msgs_;
public:
  ChatSession(boost::asio::io_service& is, ChatRoom& room): socket_(is), room_(room) {}
  boost::asio::ip::tcp::socket& socket() { return socket_; }
  void start();
  void deliver(const ChatMessage&);
  void handle_read_header(const boost::system::error_code&);
  void handle_read_body(const boost::system::error_code&);
  void handle_write(const boost::system::error_code&);
};

//-------------------------------------

//-------------------------------------

#endif /* __CHAT_H__ */
