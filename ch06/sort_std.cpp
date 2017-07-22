#include<iostream>
#include<vector>
#include<algorithm>

bool compare(int a,int b){ return (a>b); }
void output(int i){ std::cerr << i << " ";}

void sort_std(){
  int a[10] = {8,3,4,2,5,6,9,1,10,7};
  std::vector<int> b(a,a+10);

  std::sort(b.begin(),b.end());
  for(std::vector<int>::iterator n = b.begin(); n != b.end(); n++){
    std::cerr << *n << " ";
  }
  std::cout <<std::endl;

  std::sort(b.begin(),b.end(),compare);
  std::for_each(b.begin(),b.end(),output);
  std::cout << std::endl;

#if __GXX_EXPERIMENTAL_CXXOX__
  // g++ -std=c++0x -0 sort_std2 sort_std.cpp
  std::vector<int> c{8,3,4,2,5,6,9,1,10,7};
  std::sort(c.begin(),c.end());

  std::for_each(c.begin(),c.end(),[](int &n){ std::cerr << n << " " ; });
  std::cout << std::endl;

  std::sort(c.begin(),c.end(),[](int a,int b){ return (a > b); } );
  for (int n : c){
    std::cout << n << " ";
  }
  std::cout << std::endl;
#endif
}

int main(){
  int a;
  sort_std();
  return 0;
}
