#include<iostream>

int test(int i,int j){
  return(i * j);
}
int main(int argc, char * argv[]){
  int i,j,k;
  i = 3;
  j = 2;
  k = test(i,j);
  if (k>5) std::cout << ">5" << std::endl;
  else std::cout << "<=5" << std::endl;
  return 0;
}
