//gcc -o server server.c -lpthread
//% telnet localhost  12345

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<signal.h>
#include<errno.h>

#define PORT 12345

int socket_list[16];
int client_num = 0;

static pthread_mutex_t g_mutex;

int socket_read(int socket,void* buf,int buf_size){
  int size;
  int left_size = buf_size;
  char* p = (char*)buf;

  while(left_size > 0){
    size = read(socket,p,left_size);
    p += size;
    left_size -= size;

    if(size <= 0)break;
  }
  return buf_size - left_size;
}

int socket_write(int socket,void* buf, int buf_size){
  int s;
  int size;
  int left_size = buf_size;
  char* p = (char*)buf;

  while(left_size > 0){
    size = write(socket,p,left_size);
    p += size;
    left_size -= size;

    if(size == 0) break;
    if(size < 0){
      switch(errno){
      case EPIPE:
	for(s = 0;s < client_num;s++){
	  if(socket_list[s] == socket){
	    int j;
	    for(j = s;j < client_num-1;j++){
	      socket_list[j] = socket_list[j+1];
	    }
	    client_num--;
	  }
	}
	printf("Disconnected : %d\n",socket);
	return -1;
      }
      break;
    }
  }
  return buf_size - left_size;
}

void* comm(void* arg){
  int s = *(int *)arg;
  int size;
  char buf[1024];
  pthread_detach(pthread_self());
  pthread_mutex_lock(&g_mutex);
  {
    int new_client_index = client_num;
    socket_list[new_client_index] = s;
    client_num++;
  }
  pthread_mutex_unlock(&g_mutex);

  while(1){
    int i,ret;
    ret = read(s,buf,sizeof(buf));
    if(ret <= 0)return NULL;
    printf("Client: %s\n",buf);
    pthread_mutex_lock(&g_mutex);
    for(i = 0;i<client_num;i++){
      if(socket_write(socket_list[i],"echo ",5) < 0){
	return NULL;
      }
      if(socket_write(socket_list[i],buf,ret) <0){
	return NULL;
      }
    }
    pthread_mutex_unlock(&g_mutex);
  }
  return NULL;
}

void* thread_idle(void* arg){
  int loop = 0;

  pthread_detach(pthread_self());
  while(1){
    int i;

    pthread_mutex_lock(&g_mutex);
    {
      printf("client_com = %d\n",client_num);
      for(i = 0; i < client_num;i++){
	char buf[256];
	sprintf(buf,"%d\n",loop);
	printf("Sending : %s",buf);
	socket_write(socket_list[i],buf,sizeof(char)*strlen(buf));
      }
    }
    loop++;
    pthread_mutex_unlock(&g_mutex);
    sleep(1);
  }
  return NULL;
}

int main(int argc,char* argv[]){
  int i,s,ns;
  struct sockaddr_in sin;
  pthread_t thread;

  signal(SIGPIPE,SIG_IGN);

  if((s=socket(AF_INET,SOCK_STREAM,0)) < 0){
    perror("server: socket");
    exit(1);
  }
  memset((char *)&sin, 0, sizeof(struct sockaddr));

  sin.sin_family = AF_INET;
  sin.sin_port = htons(PORT);
  sin.sin_addr = htonl(INADDR_ANY);//??????????????

  if((bind(s,(struct sockaddr *)&sin,sizeof(sin))) < 0){
    perror("server: bind");
    exit(1);
  }

  if((listen(s,10))<0){
    perror("server: listen");
    exit(1);
  }

  printf("waiting for connetion at port %d\n",PORT);

  pthread_create(&thread,NULL,thread_idle,NULL);

  while(1){
    if((ns=accept(s,NULL,0))<0){
      perror("server: accept");
      continue;
    }
    printf("Connected : %d\n",ns);

    pthread_create(&thread,NULL,comm,(void*)&ns);
  }
}
