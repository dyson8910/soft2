//client.c gcc -o client client.c -lpthread

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<pthread.h>

#define PORT 12345

static int g_socket;

static pthread_t g_tr, g_ts;
static pthread_mutex_t g_mutex;

void socket_open(const char* ip_addr){
  struct sockaddr_in sin;

  if((g_socket = socket(AF_INET,SOCK_STREAM,0))<0){
    perror("client: socket");
    exit(1);
  }

  sin.sin_family = AF_INET;
  sin.sin_port  htons(PORT);
  sin.sin_addr.s_addr = inet_addr(ip_addr);

  if((connect(g_socket,(struct sockaddr *)&sin,sizeof(sin)))<0){
    perror("client: connect");
    exit(1);
  }
}

void socket_close(){
  close(g_socket);
}

int socket_read(int socket, void* buf, int buf_size){
  int size;
  int left_size = buf_size;
  char* p = (char *) buf;

  while(left_size > 0){
    size = read(socket,p,left_size);
    p += size;
    left_size -= size;

    if(size <= 0)break;
  }
  return buf_size - left_size;
}

int socket_write(int socket,void* buf, int buf_size){
  int size;
  int left_size =buf_size;
  char* p = (char *)buf;

  while(left_size > 0){
    size = write(socket,p,left_size);
    p += size;
    left_size -= size;
    if(size <= 0)break;
  }
  return buf_size - left_size;
}

void* thread_recv(void* arg){
  char buf[1024];
  int size;

  while(1){
    size = read(g_socket,buf,sizeof(buf));
    printf("Received : %s",buf);
  }
  return NULL;
}

int main(int argc,char* argv[]){
  if(argc == 1){
    printf("usage: client <server IP address\n");
    exit(1);
  }

  socket_open(argv[1]);
  pthread_mutex_init(&g_mutex,NULL);
  pthread_create(&g_tr,NULL,thread_recv,NULL);
  pthread_join(g_tr,NULL);
  return 0;
}
