#define BOOST_TEST_MODULE ListTest
#include <boost/test/unit_test.hpp>

#include "forward_list.h"

BOOST_AUTO_TEST_CASE(Insert){
	forward_list<int> my_list;
	BOOST_CHECK(my_list.size()==0);
	for(int i=1; i<=10; ++i){
		my_list.append(i);
		BOOST_CHECK(my_list.size()==i);
	}
}

