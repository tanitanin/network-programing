#include <stdio.h>
#include <stdlib.h> // exit
#include <string.h> // bzero
#include <sys/types.h>
#include <sys/socket.h> // socket,bind,listen,accept,recv
#include <netinet/in.h> // htons
#include <unistd.h>

#define BUFSIZE 1024
#define PORT 40320

int main(int argc, char **argv)
{
  struct sockaddr_in saddr; // address for server
  struct sockaddr_in caddr; // address for client

  int listen_fd;
  int conn_fd;

  int len = sizeof(caddr);

  int rsize;
  char buf[BUFSIZE];

  // generate socket
  if((listen_fd = socket(AF_INET, SOCK_STREAM, 0))<0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }
  printf("generated socket.\n");

  bzero((char *)&saddr, sizeof(saddr));

  // bind
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = INADDR_ANY;
  saddr.sin_port = htons(PORT);
  if(bind(listen_fd, (struct sockaddr *)&saddr, len) < 0) {
    perror("bind");
    exit(EXIT_FAILURE);
  }
  printf("binded\n");

  // listen
  if(listen(listen_fd, 5) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
  printf("Start listening port %d ...\n", PORT);

  while(1) {
    len = sizeof(caddr);

    // connection
    if((conn_fd = accept(listen_fd,(struct sockaddr *)&caddr,&len)) < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
    }
    close(listen_fd);
    
    // read
    while(rsize = read(conn_fd, buf, BUFSIZE)) {
      write(conn_fd, buf, rsize);
    }
    close(conn_fd);
  }
  
  return 0;
}
