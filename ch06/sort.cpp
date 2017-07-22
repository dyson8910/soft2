#include<iostream>
#include<vector>
#include<algorithm>
#include<boost/assign/std/vector.hpp>
#include<boost/assign/list_of.hpp>
#include<boost/foreach.hpp>
#include<boost/lambda/bind.hpp>
#include<boost/lambda/lambda.hpp>
#include<boost/range/algorithm.hpp>
using namespace boost::assign;
using namespace boost::lambda;

void sort_boost(){
  std::vector<int> a;
  a += 8,3,4,2,5,6,9,1,10,7;

  boost::sort(a);
  BOOST_FOREACH(int &n, a){
    std::cout << n << " ";
  }
  std::cout << std::endl;

  boost::sort(a, (_1 > _2));
  std::for_each(a.begin(),a.end(),std::cout << _1 << " ");
  std::cout << std::endl;

  typedef std::pair<int,std::string>pair_type;
  std::vector<std::pair<int,std::string> > b = boost::assign::list_of
    (pair_type(8, "eight")) (pair_type(3, "three")) (pair_type(4, "four"))
    (pair_type(2, "two"))   (pair_type(5, "five"))  (pair_type(6, "six"))
    (pair_type(9, "nine"))  (pair_type(1, "one"))   (pair_type(10, "ten")) (pair_type(7, "seven"));

  std::sort(b.begin(),b.end(),
	    boost::lambda::bind<int>(&pair_type::first, _1) >
	    boost::lambda::bind<int>(&pair_type::first, _2));
  std::for_each(b.begin(),b.end(),
		std::cout << boost::lambda::bind(&pair_type::first, _1) << ":"
		<< boost::lambda::bind(&pair_type::second, _1) << " ");
  std::cout << std::endl;

#if __cplusplus >= 201103L
  // g++ -std=c++11 -o sort-c11 sort.cpp
  std::cerr << "using boost::sort and c++11 lambda function" << std::endl;
  boost::sort(a,[](int a,int b){return ( a < b );});
  boost::for_each(a,[](int &n){ std::cerr << n << " ";});
  std::cout << std::endl;
  boost::sort(a,[](int a,int b){return ( a > b );});
  boost::for_each(a,[](int &n){ std::cerr << n << " ";});
  std::cout << std::endl;
#endif

#if __cplusplus >= 201401L
  // g++ -std=c++14 -o sort-c14 sort.cpp
  std::cerr << "using boost::sort and c++14 generic lambda function" << std::endl;
  boost::sort(a,[](auto a,auto b){return ( a < b );});
  boost::for_each(a,[](auto &n){ std::cerr << n << " ";});
  std::cout << std::endl;
  boost::sort(a,[](auto a,auto b){return ( a > b );});
  boost::for_each(a,[](auto &n){ std::cerr << n << " ";});
  std::cout << std::endl;
#endif

#ifdef BOOST_RANGE_ALGORITHM_SORT_HPP_INCLUDED
  std::cerr << "BOOST_FOREACH" << std::endl;
  std::vector<int> c;
  c += 8,3,4,2,5,6,9,1,10,7;
  BOOST_FOREACH(int &n,boost::sort(c)){
    std::cout << n << " ";
  }
  std::cout << std::endl;
  BOOST_FOREACH(int &n,boost::unique(boost::sort(c))){
    std::cout << n << " ";
  }
  std::cout << std::endl;
#endif
}

int main(){
  std::cout << "C++ + boost" << std::endl;
  sort_boost();
  return 0;
}
