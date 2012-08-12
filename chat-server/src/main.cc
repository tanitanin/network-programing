
#include "socket.h"
#include <boost/asio.hpp>

using namespace std;

int main(int argc, char **argv)
{
  Socket socket = Socket();
  socket.echo_server();
  return 0;
}
