#include <iostream>
#include "allocator.h"
#include "forward_list.h"
#include <map>
#include <utility>
int fact[100];
void calculate_factorials(int n){
	fact[0]=1;
	for(int i=1; i<=n; ++i)
		fact[i]=fact[i-1]*i;
}
int main(){
	calculate_factorials(10);

	std::map<int,int> mp1;

	for(int i=0; i<10; ++i)
		mp1[i]=fact[i];
	
	for(auto it:mp1)
		std::cout<<it.second<<" ";
	std::cout<<std::endl;
	
	
	std::map<int,int,std::less<int>,my::my_allocator<std::pair<const int,int>,10>> mp2;
	for(int i=0; i<10; ++i)
		mp2[i]=fact[i];
	for(auto it:mp2)
		std::cout<<it.second<<" ";
	std::cout<<std::endl;
	
	forward_list<int> list1;
	for(int i=0; i<10; ++i)
		list1.append(i);
	list1.print(std::cout);
	std::cout<<std::endl;

	forward_list<int,my::my_allocator<int,10>> list2;
	for(int i=0; i<10; ++i)
		list2.append(i);
	list2.print(std::cout);
}
