#include <stdlib.h>

// constructing bitsets
#include <iostream>       // std::cout
#include <string>         // std::string
#include <bitset>         // std::bitset


// convert bitsets to signed signed integers
template<std::size_t bitsetSize>
long bitset_to_long(const std::bitset<bitsetSize>& b ) {
	struct { long x:bitsetSize; } s;

	// only the bitsetSize bits will be used
	return s.x = b.to_ulong();
}



int main ()
{
	std::bitset<16> foo;
	std::bitset<16> bar (0xfa2);
	std::bitset<31> b31 (-1);

	// 从字符串的第2位，开始读入4个字符，用于初始化bitset
	// str = "1100"  ==> cout << bitset 1100  ==> bitset[0] == 0
	std::bitset<16> baz (std::string("0101111001"), 2, 4 ); //"0111"

	std::cout << "foo" << foo << '\n';
	std::cout << "bar" << bar << '\n';
	std::cout << "baz: " << baz << "\tbaz[0]:" << baz[0] << '\n'; //baz[0] == 1

	std::cout << "b31(-1) using casting: " << static_cast<int>(b31.to_ulong() ) << std::endl;
	std::cout << "b31(-1) using bitfield trick: " << bitset_to_long(b31) << std::endl;

return 0;
}

