#include<stdio.h>

int tarai(int x,int y, int z){
  if(x<=y){
    return y;
  }else{
    return tarai(tarai(x-1,y,z),tarai(y-1,x,z),tarai(z-1,x,y));
  }
}

int main(void){
  int x,y,z,t;
  printf("x:");
  scanf("%d",&x);
  printf("y:");
  scanf("%d",&y);
  printf("z:");
  scanf("%d",&z);
  t = tarai(x,y,z);
  printf("%d\n",t);
  return 0;
}
