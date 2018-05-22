#ifndef H_FORWARD
#define H_FORWARD
#include <memory>
#include <iostream>
using namespace std;
template <typename T, typename Alloc = allocator<T>>
class forward_list{
private:
	struct Node{
		shared_ptr<Node> nxt;
		T value;
		Node():nxt{},value{T()}{}
		Node(const Node & rhs):nxt(rhs.nxt),value(rhs.value){}
	};
	
	int _size=0;	

	struct Deleter{
		void operator()(Node * el){}
	};

	using ptr =shared_ptr<Node>;
	using allocator_type = typename allocator_traits<Alloc>:: template rebind_alloc<Node>;
	using traits = allocator_traits<allocator_type>; 
	
	allocator_type _allocator;
	ptr head;
	ptr tail;

public:
	forward_list(){
		tail = ptr(traits::allocate(_allocator,1),Deleter());
		tail->nxt=ptr(nullptr);
		head=tail;
	} 
	int size(){
		return _size;
	}
	void append(T & element){
		ptr new_node(traits::allocate(_allocator,1),Deleter());
		
		new_node->nxt=head;
		new_node->value=element;
		head = new_node;
		++_size;
	}
	void print(ostream & stream,string delim=" "){
		for (auto curr=head; curr!=tail; curr=curr->nxt)
			stream<<curr->value<<delim;
	}
};
	
#endif
