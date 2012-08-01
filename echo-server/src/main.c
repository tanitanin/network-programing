#include <stdio.h>
#include <stdlib.h> // exit
#include <string.h> // bzero
#include <sys/types.h>
#include <sys/socket.h> // socket,bind,listen,accept,recv
#include <netinet/in.h> // htons
#include <unistd.h>
#include <pthread.h>

#define BUFSIZE 1024
#define PORT 40320

int server_socket(void);
int accept_loop(int);

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
  socklen_t len;
  pthread_t tid;
  void process(void *);
  
  while(1) {
    len = (socklen_t) sizeof(caddr);
    
    // connection
    if((conn_fd = accept(listen_fd,(struct sockaddr *)&caddr,&len)) < 0) {
      perror("accept");
      return -1;
    }
    printf("Connected.\n");
    
    if(pthread_create(&tid,NULL,&process,(void *)conn_fd)!=0) {
      perror("thread create");
      return -2;
    }
  }
}

// processing after accepted
void process(void *arg)
{
  printf("process start.\n");
  // thread detach
  pthread_detach(pthread_self());
  
  int conn_fd = (int) arg;
  int rsize;
  char buf[BUFSIZE];
  
  // read
  while(rsize = read(conn_fd, buf, BUFSIZE)) {
    write(conn_fd, buf, rsize);
  }
  close(conn_fd);
  pthread_exit((void *)0);
}

// main function
int main(int argc, char **argv)
{
  int listen_fd;
  
  if((listen_fd = server_socket())<0) {
    perror("socket");
    exit(EXIT_FAILURE);
  }
  printf("Socket generated.\n");
  
  accept_loop(listen_fd);
  printf("accept_loop ended.\n");
  
  close(listen_fd);
  return 0;
}
