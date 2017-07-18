#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int shared_resource = 0;

int main(){
  pid_t pid;
  pid = fork();
  if(pid == 0){
    int i;
    for(i = 0; i < 10; i++){
      printf("Process [%d]: %d\n",pid,i);
      shared_resource++;
      sleep(1);
    }
    printf("Process [%d]:finished, return %d.\n",pid,shared_resource);
    exit(0);
  }else if(pid >0){
    int i;
    for(i = 0; i < 10; i++){
      printf("Process %d: %d\n",pid,i);
      shared_resource++;
      usleep(300*1000);
    }
    int status;
    wait(&status);
    printf("Process %d finished, return %d.\n",pid,shared_resource);
  }
  return 0;
}
