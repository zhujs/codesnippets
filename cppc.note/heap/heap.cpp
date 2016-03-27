


template<typename Type, typename Compare >
bool heap<Type, Compare>::insert( const Type& ele )
{

	//put the eleemnt at the end
	data.push_back( ele );

	for( ssize_t ind = size(); ind > 1; ind /= 2 )
	{
		if( comp( data[ind/2 -1 ], data[ind-1] ) )
			break;

		std::swap( data[ind -1 ], data[ind/2 -1] );
	}
}

template<typename Type, typename Compare >
Type heap<Type, Compare>::remove()
{
	Type ret = data[0];

	//relace the top element with the last element 
	data[0] = data[size()-1];

	//erase the last
	data.erase(data.end()-1);

	//adjust the heap
	heapAdjust(0);

	return ret;
}

template<typename Type, typename Compare>
Type heap<Type, Compare>::get() const
{
	return data[0];
}

template<typename Type, typename Compare >
void heap<Type, Compare>::heapAdjust(ssize_t ind)
{
	Type temp = data[ind];


	for( ssize_t index=(ind+1) * 2; index<=size(); index *= 2 )
	{
		//find the maximum or minimum child node
		if( index+1<= size() && comp(data[index],data[index-1]) )
			index += 1;
				

		if( comp( temp, data[index-1] ) )
			break;
		
		data[ind] =  data[index-1] ;
		ind = index -1;
	}		

	data[ind] = temp;
}

template<typename Type, typename Compare >
void heap<Type, Compare>::buildHeap()
{
	//built the heap
	for(int ind = size()/2; ind >=1; ind-- )
	{
		heapAdjust(ind-1);
	}
}







