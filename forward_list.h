#ifndef H_FORWARD
#define H_FORWARD
#include <memory>
#include <iostream>
#include "allocator.h"
using namespace std;
template <typename T, typename Alloc = allocator<T>>
struct forward_list{

	struct Node{
		Node * nxt;
		T value;
	};
	
	using allocator_type = typename allocator_traits<Alloc>:: template rebind_alloc<Node>;
	using traits = allocator_traits<allocator_type>; 
	
	allocator_type _allocator;
	Node * head;
	Node * tail;

	forward_list(){
		tail = traits::allocate(_allocator,1);
		tail->nxt=nullptr;
		head=tail;
	} 
	void append(T & element){
		Node * new_node = traits::allocate(_allocator,1);
		new_node->nxt=head;
		new_node->value=element;
		head = new_node;
	}
	void print(ostream & stream){
		for (auto curr=head; curr!=tail; curr=curr->nxt)
			stream<<curr->value<<" ";
	}
};
	
#endif
