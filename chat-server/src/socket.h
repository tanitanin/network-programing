#ifndef __SOCKET_H__
#define __SOCKET_H__

#include <cstdio>
#include <cstdlib> // exit
#include <cstring> // bzero
#include <sys/types.h>
#include <sys/socket.h> // socket,bind,listen,accept,recv
#include <netinet/in.h> // htons
#include <unistd.h>
#include <pthread.h>

#include <boost/array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

#define BUFSIZE 1024
#define PORT 40320

class SocketBase
{
private:
  boost::asio:ip::tcp::socket _socket;
  boost::array<char, #BUFSIZE> buffer;
  
protected:
  int run();
  
public:
  SocketBase();
  ~SocketBase();
  int connect();
  int receive();
  int read();
  int send();
};

class Socket
{
public:
  int server_socket(void);
  int accept_loop(int);
  int accept_loop(int,void *(*)(void *));
  void *process(void *arg);
  void echo_server(void);
};


#endif // __SOCKET_H__

