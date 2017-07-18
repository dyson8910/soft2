#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

long int shared_resource = 0;

void *task(void *arg){
  long int i,loop = (long)arg;
  for(i=0;i<loop;i++){
    printf("Thread [%x]: %ld\n",(int)pthread_self(),i);
    shared_resource++;
    usleep(10*1000*1000/loop);
  }
  arg = (void *)(shared_resource);
}

int main(){
  pthread_t thread1, thread2;
  long int loop1 = 10,loop2 = 20;

  pthread_create(&thread1,NULL,task,(void *)loop1);
  pthread_create(&thread2,NULL,task,(void *)loop2);

  int ret1,ret2;
  pthread_join(thread1,(void **)&ret1);
  printf("Thread[%d]: finished,return %d.\n",(int)thread1,ret1);
  pthread_join(thread2,(void **)&ret2);
  printf("Thread[%d]: finished,return %d.\n",(int)thread2,ret2);

  return 0;
}
