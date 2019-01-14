#include "MyInt.hpp"
#include<chrono>

using namespace std::chrono;

namespace cs540{

class Array{
  private:
    MyInt *a;
  public:
    int count_a;
  public:
    Array(std::initializer_list<int>list1){
      count_a=0;
      for(auto temp=list1.begin();temp<list1.end();temp++){
        count_a++;
      }
      a=new MyInt[count_a];
      int i=0;
      for(auto temp=list1.begin();temp<list1.end();temp++){
        a[i++]=*temp;
        //std::cout<<a[i++]<<std::endl;
      }
    }

    friend std::ostream &operator<<(std::ostream &o1,Array &a1){
      int i1, j=a1.count_a;
      i1 = 0;
      for(i1=0;i1<j;i1++){
        o1<<(a1.a[i1]);
        if(i1!=a1.count_a-1)
          o1<<", ";
      }
      return o1;
    }

    Array(const Array &a2){
      a=new MyInt[a2.count_a];
      count_a=a2.count_a;
      //std::cout << "hdfgj" << count_a << "::::::::::::jdfgtf: " << a2.count_a << std::endl;
      for(int i=0;i<a2.count_a;i++){
        //std::cout << "hdfgj" <<std::endl;
        a[i]=a2.a[i];
      }
    }

    Array(Array &&a2){
      count_a=a2.count_a;
      a=a2.a;
      a2.a=NULL;
      a2.count_a=0;
    }

    Array & operator = (Array &a2){
      count_a=a2.count_a;
      a=new MyInt[a2.count_a];
      for(int i=0;i<a2.count_a;i++){
        a[i]=a2.a[i];
      }
      return *this;
    }

    Array & operator = (Array &&a2){
      count_a=a2.count_a;
      a=a2.a;
      a2.a=NULL;
      a2.count_a=0;
      return *this;
    }

    Array(){
      count_a = 0;
    }


    static void move_performance_test() {
		  std::cout<<"move_performance_test"<<std::endl;
	    Array a1{};
		  a1.a = new MyInt[10000000];
		  for (long i = 0; i < 10000000; ++i) {
			    a1.a[i] = i;
          a1.count_a++;
		  }

		high_resolution_clock::time_point t1 = high_resolution_clock::now();
		Array a2{a1};
		high_resolution_clock::time_point t2 = high_resolution_clock::now();
    auto dur = duration_cast<microseconds>(t2-t1).count();
    std::cout << "Copy constructor of 10000000 elements of Array: " << dur << " microseconds" <<std::endl;

		auto duration = duration_cast<microseconds>(t2-t1).count();
    t1 = high_resolution_clock::now();
		Array a3{std::move(a1)};
    t2 = high_resolution_clock::now();
    dur = duration_cast<microseconds>(t2-t1).count();
    std::cout << "Move constructor of 10000000 elements of Array: " << dur << " microseconds" <<std::endl;


    t1 = high_resolution_clock::now();
    Array a4{};
    a4=a2;
    t2 = high_resolution_clock::now();
    dur = duration_cast<microseconds>(t2-t1).count();
    std::cout << "Copy assignment of 10000000 elements of Array: " << dur << " microseconds" <<std::endl;

    t1 = high_resolution_clock::now();
    Array a5{};
    a5=std::move(a2);
    t2 = high_resolution_clock::now();
    dur = duration_cast<microseconds>(t2-t1).count();
    std::cout << "Move assignment of 10000000 elements of Array: " << dur << " microseconds" <<std::endl;

	}
};
}
