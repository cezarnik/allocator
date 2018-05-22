#include "forward_list.h"
#include <map>
#include <utility>
#include <algorithm>
#include <iterator>
#include "allocator.h"
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
	std::generate_n(std::inserter(mp1, std::begin(mp1)), 10, make_factorials);

	for (auto it: mp1)
		std::cout<<it.second<<"\n";
	
	std::map<int,int,std::less<int>,my::my_allocator<std::pair<const int,int>,10>> mp2;
	std::generate_n(std::inserter(mp2, std::begin(mp2)), 10, make_factorials);

	for(auto it:mp2)
		std::cout<<it.second<<"\n";


	forward_list<int> list1;
	for(int i=0; i<10; ++i)
		list1.append(i);
	list1.print(std::cout,"\n");
	
	forward_list<int,my::my_allocator<int,10>> list2;
	for(int i=0; i<10; ++i)
		list2.append(i);
	list2.print(std::cout,"\n");
}
