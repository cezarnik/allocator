#include <cstdlib>
#include <stdio.h>
#include <new>

namespace my{
	std::size_t alloc_counter = 0;
	
	void * malloc(std::size_t size) throw (std::bad_alloc){
		void * p = std::malloc(size);
		++alloc_counter;
	//	printf("malloc: %zu %p %zu\n", ++alloc_counter, p, size);
		return p; 
	}
	void free(void * p ) noexcept{
		--alloc_counter;
	//	printf("free %zu %p\n", --alloc_counter, p);
		std::free(p);
	}
}
