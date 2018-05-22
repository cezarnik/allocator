#ifndef H_ALLOCATOR
#define H_ALLOCATOR
#include <memory>
#include <vector>
#include <array>
#include <utility>
#include <iostream>
#include <map>
#include "debug.h"
namespace my{
template <typename T,std::size_t capacity=32>
class my_allocator{
	static_assert(capacity!=0, "wrong capacity");
private:
	std::vector<std::vector<std::array<char,sizeof(T)>>> pool;
	std::size_t number_of_elements=0;
	std::size_t allocated_number=0;
	const int INF=1e9;

	void add_block(){
		allocated_number+=capacity;
		auto prev_size=pool.size();
		pool.resize(prev_size+1);			
		pool.back().resize(capacity);
	}
public:	
	using value_type = T;
	using pointer =T*;	
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T &;	
	template<class U> struct rebind {using other =my_allocator<U,capacity>;};
	T* allocate(size_t n){
		if (n!=1)
			throw std::invalid_argument("can't allocate n!=1 elements with my_allocator");
		number_of_elements++;
		if (number_of_elements>allocated_number){
			add_block();
		}
		size_t index=number_of_elements-1;
		return reinterpret_cast<T*> (&pool[index/capacity][index%capacity]);			
	}
	void deallocate(T *p, size_t n){}
	void destroy(T *p){
		p->~T();
	}
};

}
#endif
