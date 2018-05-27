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
BOOST_AUTO_TEST_CASE(EqualElementsTest){
	class MyClass{
	public:
		int value;
	};
	forward_list<MyClass> my_class_list;
	BOOST_CHECK(my_class_list.size()==0);
	MyClass sample_element{2};
	BOOST_CHECK(sample_element.value==2);
	for(int i=1; i<=100; ++i){
		my_class_list.append(sample_element);
		BOOST_CHECK(my_class_list.size()==i);
	}
}

