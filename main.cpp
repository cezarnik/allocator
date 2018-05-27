#include "debug.h"
#include "forward_list.h"
#include "allocator.h"
#include <map>
#include <utility>
#include <algorithm>
#include <iterator>
constexpr auto factorial(auto n) -> decltype(n) {
	return n ? n*factorial(n-1) : 1;
}

int main(){

	auto make_factorials = [i=0] () mutable {
		auto f = factorial(i);
		auto value = std::make_pair(i,f);
		++i;
		return value;
	};
	
	std::map<int,int> mp1;
	
	try{
		std::generate_n(std::inserter(mp1, std::begin(mp1)), 10, make_factorials);
	}
	catch(const bad_alloc& e){
		std::cerr<<"exception with generate_n() on mp1: can't allocate memory"<<std::endl;
		return EXIT_FAILURE;
	}
	
	for (auto it: mp1)
		std::cout<<it.second<<"\n";
	
	
	std::map<int,int,std::less<int>,my::my_allocator<std::pair<const int,int>,10>> mp2;
	try{
		std::generate_n(std::inserter(mp2, std::begin(mp2)), 10, make_factorials);
	
	}
	catch(const std::bad_alloc& e){
		std::cerr<<"exception with generate_n() on mp2: can't allocate memory"<<std::endl;
		return EXIT_FAILURE;
	}
	for(auto it:mp2)
		std::cout<<it.second<<"\n";


	forward_list<int> list1;
	try{
		for(int i=0; i<10; ++i)
			list1.append(i);
	}
	catch(const std::bad_alloc& e){
		std::cerr<<"exception with generate_n() on list1: can't allocate memory"<<std::endl;
		return EXIT_FAILURE;
	}
	list1.print(&std::cout,"\n");
	
	forward_list<int,my::my_allocator<int,10>> list2;
	try{
		for(int i=0; i<10; ++i)
			list2.append(i);
		
	}
	catch(const bad_alloc& e){
		std::cerr<<"exception with generate_n() on list2: can't allocate memory"<<std::endl;
		return EXIT_FAILURE;
	}
	list2.print(&std::cout,"\n");
}
