#ifndef H_FORWARD
#define H_FORWARD
#include <memory>
#include <iostream>
using namespace std;
template <typename T, typename Alloc = allocator<T>>
class forward_list{
private:
	struct Deleter;
	struct Node{
		T value;
		unique_ptr<Node,Deleter> nxt;
		Node():nxt{nullptr},value{T()}{}
		Node(const Node & rhs):nxt(rhs.nxt),value(rhs.value){}
	};
	struct Deleter{
		void operator()(Node *p){}
		Deleter(){}
		Deleter(const Deleter&){}
		Deleter(Deleter&){}
		Deleter(Deleter&&){}
		Deleter & operator = (const Deleter &) = default; 
	};	
	int _size=0;	
	using allocator_type = typename allocator_traits<Alloc>:: template rebind_alloc<Node>;
	using traits = allocator_traits<allocator_type>; 
	
	allocator_type _allocator;
	unique_ptr<Node,Deleter> head;
	Node * tail = nullptr;

public:
	int size(){
		return _size;
	}
	void append(T & element){
			
		unique_ptr<Node,Deleter> new_node(_allocator.allocate(1),Deleter());

		new_node->nxt=unique_ptr<Node,Deleter>(head.release());	
		new_node->value=element;
		head = std::move(new_node);
		++_size;
	}
	void print(ostream * stream,string delim=" "){
		for (auto curr=head.get(); curr; curr=curr->nxt.get())
			(*stream)<<curr->value<<delim;
	}
};
	
#endif
