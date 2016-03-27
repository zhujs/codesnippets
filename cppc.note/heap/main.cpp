
#include<iostream>
#include<functional>
#include"heap.h"

using namespace std;


int main()
{
	int data[] = { 4, 55, 9, 23, 7, 44, 9, 55 };

	//get a min heap
	
	
	heap<int,greater<int> > minHeap(data ,data+ sizeof(data)/sizeof(*data) );

	minHeap.insert(10);
	for(ssize_t i = 0; i< sizeof(data)/sizeof(*data); ++i)
	{
		cout << minHeap.remove() << endl;
	}
	return 0;
}


