#define BOOST_TEST_MODULE alloc_test

#include <boost/test/unit_test.hpp>

#include "debug.h"
#include "allocator.h"

BOOST_AUTO_TEST_CASE(Leaks) {
	int initial=my::alloc_counter;
	{	
		my::my_allocator<int,10> alloc;
		for(int i=0; i<30; ++i){
			auto pointer = alloc.allocate(1); 
			BOOST_CHECK(pointer!=nullptr);
		}		
	}
	BOOST_CHECK(my::alloc_counter==initial); //check for leaks
}

BOOST_AUTO_TEST_CASE(ChunkCheck) {
	my::my_allocator<int,15> alloc;
	int initial=my_alloc_counter;
	
	auto pointer = alloc.allocate(1);
	BOOST_CHECK(pointer!=nullptr);
	BOOST_CHECK(my::alloc_counter==initial+15); //number of preallocated elements
	
}
