#include <stdio.h>
#include <stdlib.h> // exit
#include <string.h> // bzero
#include <sys/types.h>
#include <sys/socket.h> // socket,bind,listen,accept,recv
#include <netinet/in.h> // htons
#include <unistd.h>

#define BUFSIZE 1024
#define PORT 40320

// socket bind and listen
int server_socket(void)
{
  struct sockaddr_in saddr; // address for server
  int len = sizeof(saddr);
  int listen_fd;
  
  // generate socket
  if((listen_fd = socket(AF_INET, SOCK_STREAM, 0))<0) {
    perror("socket");
    return -1;
  }
  
  // bind
  bzero((char *)&saddr, sizeof(saddr));
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = INADDR_ANY;
  saddr.sin_port = htons(PORT);
  if(bind(listen_fd, (struct sockaddr *)&saddr, len) < 0) {
    perror("bind");
    return -2;
  }
  
  // listen
  if(listen(listen_fd, 5) < 0) {
    perror("listen");
    return -3;
  }
  return listen_fd;
}

// accept loop
int accept_loop(int listen_fd)
{
  int conn_fd;
  struct sockaddr_in caddr; // address for client
  int len = sizeof(caddr);
  int rsize;
  char buf[BUFSIZE];
  int pid;

  while(1) {
    len = sizeof(caddr);
    
    // connection
    if((conn_fd = accept(listen_fd,(struct sockaddr *)&caddr,&len)) < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
    }
    
    if((pid = fork()) == 0) {
      // read
      while(rsize = read(conn_fd, buf, BUFSIZE)) {
        write(conn_fd, buf, rsize);
      }
      close(conn_fd);
      exit(0);
    }
    close(conn_fd);
  }
}

int main(int argc, char **argv)
{
  int listen_fd;

  if((listen_fd = server_socket())<0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }
  
  accept_loop(listen_fd);
  
  close(listen_fd);
  return 0;
}
