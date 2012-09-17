//

//-------------------------------------
#include <iostream>
#include <boost/bind.hpp>
#include "chat.h"
//-------------------------------------
bool ChatMessage::decode_header()
{
  char header[header_length+1] = "";
  std::strncat(header, data_, header_length);
  body_length_ = std::atoi(header);
  if(body_length_ > max_body_length) {
    body_length_ = 0;
    return false;
  }
  return true;
}
void ChatMessage::encode_header()
{
  char header[header_length+1] = "";
  std::sprintf(header, "%4d", body_length_);
  std::memcpy(data_, header, header_length);
}

//-------------------------------------
void ChatRoom::join(chat_participant_ptr participant)
{
  participants_.insert(participant);
  std::for_each(recent_msgs_.begin(),recent_msgs_.end(),
                boost::bind(&ChatParticipant::deliver, participant, _1));
}
void ChatRoom::leave(chat_participant_ptr participant)
{
  participants_.erase(participant);
}
void ChatRoom::deliver(const ChatMessage& msg)
{
  recent_msgs_.push_back(msg);
  while(recent_msgs_.size() > max_recent_msgs)
    recent_msgs_.pop_front();
  
  std::for_each(participants_.begin(), participants_.end(),
                boost::bind(&ChatParticipant::deliver, _1, boost::ref(msg)));
}

//-------------------------------------
void ChatSession::start()
{
  room_.join(shared_from_this());
  boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.data(), ChatMessage::header_length),
        boost::bind(&ChatSession::handle_read_header, shared_from_this(),
                    boost::asio::placeholders::error));
}

void ChatSession::deliver(const ChatMessage& msg)
{
  bool write_in_progress = !write_msgs_.empty();
  write_msgs_.push_back(msg);
  if (!write_in_progress) {
    boost::asio::async_write(socket_,
        boost::asio::buffer(write_msgs_.front().data(),
                            write_msgs_.front().length()),
        boost::bind(&ChatSession::handle_write, shared_from_this(),
                    boost::asio::placeholders::error));
  }
}
void ChatSession::handle_read_header(const boost::system::error_code& error)
{
  if (!error && read_msg_.decode_header()) {
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.body(), read_msg_.body_length()),
        boost::bind(&ChatSession::handle_read_body, shared_from_this(),
                    boost::asio::placeholders::error));
  } else {
    room_.leave(shared_from_this());
  }
}
void ChatSession::handle_read_body(const boost::system::error_code& error)
{
  if(!error) {
    room_.deliver(read_msg_);
    boost::asio::async_read(socket_,
        boost::asio::buffer(read_msg_.data(), ChatMessage::header_length),
        boost::bind(&ChatSession::handle_read_header, shared_from_this(),
                    boost::asio::placeholders::error));
  } else {
    room_.leave(shared_from_this());
  }
}
void ChatSession::handle_write(const boost::system::error_code& error)
{
  if(!error) {
    write_msgs_.pop_front();
    if (!write_msgs_.empty()) {
      boost::asio::async_write(socket_,
          boost::asio::buffer(write_msgs_.front().data(),
                              write_msgs_.front().length()),
          boost::bind(&ChatSession::handle_write, shared_from_this(),
                      boost::asio::placeholders::error));
    }
 }else{
     room_.leave(shared_from_this());
  }
}
//-------------------------------------
