
#ifndef HEAP_GUARD
#define HEAP_GUARD

/*
 * Implement a template Heap ( max heap or min heap, default to min heap );
 *
 */
 

#include<vector>
#include<cstdlib>
#include<functional>

template <typename Type, typename Compare = std::less<Type> >
class heap
{
	public:
	 	heap(){}
	 	explicit heap(const Compare& c ):comp(c) {}

		//constructor
		template <class InputIterator>
		heap( InputIterator first, InputIterator last):data(first, last) 
		{ buildHeap(); }

		template <class InputIterator>
		heap( InputIterator first, InputIterator last, const Compare& c):data(first, last),comp(c) 
		{ buildHeap(); }

		// insert an element to heap;
		bool insert( const Type& ele );

		// remove the element at the top of heap;
		Type remove();

		// get the element at the top of heap;
		Type get() const;

		ssize_t size() const { return data.size(); }
	private:
		std::vector<Type> data;
		Compare comp;

		//adjust the heap, make data[rootIndex, size()] to be a heap 
		void heapAdjust(ssize_t ind);

		//build the heap
		void buildHeap();


};

#include"heap.cpp"



#endif
