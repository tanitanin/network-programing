#ifndef __CHATROOM_H_
#define __CHATROOM_H_

#include <vector>

#include "user.h"

using namespace std;

class ChatRoom
{
private:
  vector<User> users;

public:
  void add(User u);
  void remove(User u);
  void throwMessage(Message m);
}

#endif // __CHATROOM_H_
