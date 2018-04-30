#ifndef H_ALLOCATOR
#define H_ALLOCATOR
#include <memory>
#include <vector>
#include <array>
#include <bitset>
#include <utility>
#include <iostream>
#include <set>
#include <map>
//#include "debug.h"
namespace my{
template <typename T,std::size_t capacity=32>
class my_allocator{
	static_assert(capacity!=0, "wrong capacity");
private:
	std::vector<std::vector<std::array<char,sizeof(T)>>> pool;
	std::size_t number_of_elements=0;
	std::size_t allocated_number=0;
	std::vector<std::pair<int,int>> free_places;
	std::set<std::pair<T*,int>> heads;
	const int INF=1e9;

	void add_block(){
		allocated_number+=capacity;
		pool.push_back(std::vector<std::array<char,sizeof(T)>>(capacity));			
		heads.insert(std::make_pair(reinterpret_cast<T*>(&pool.back()[0]),static_cast<int>(pool.size()-1)));
	}
public:	
	using value_type = T;
	using pointer =T*;	
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T &;	
	template<class U> struct rebind {using other =my_allocator<U,capacity>;};
	T* allocate(size_t n){
//		std::cout<<"allocate "<<n<<std::endl;
		if (n!=1)
			throw std::invalid_argument("can't allocate n!=1 elements with my_allocator");
		if (!free_places.empty()){
			auto position=free_places.back();
			free_places.pop_back();
			return reinterpret_cast<T*>(&pool[position.first][position.second]);
		}
		number_of_elements++;
		if (number_of_elements>allocated_number){
			add_block();
		}
		size_t index=number_of_elements-1;
		return reinterpret_cast<T*> (&pool[index/capacity][index%capacity]);
			
	}
	void deallocate(T *p, size_t n){
		auto it=heads.upper_bound(std::make_pair(p,INF));
		--it;
		int pool_ind=it->second;
		for (int i=0; i<capacity; ++i){
			if (reinterpret_cast<T*>(&pool[pool_ind][i])==p){
				free_places.push_back(std::make_pair(pool_ind,i));
				break;
			}
		}
	}
	void destroy(T *p){
		p->~T();
	}
};

}
#endif
